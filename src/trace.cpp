#include "trace.h"

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "camera.h"
#include "hitobject.h"
#include "hitrecord.h"
#include "material.h"
#include "ray.h"

using std::vector;
using std::unique_ptr;
using std::make_unique;
using glm::vec3;

void Tracer::trace(HitObject* world, Camera& cam, ImgData& img_data,
                   int samples_per_pix) const
{
  int nx = img_data.nx;
  int ny = img_data.ny;
  int n_channels = img_data.n_channels;
  img_data.data = std::vector<int>(nx * ny * n_channels);

  for (int j = ny - 1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      vec3 col(0.f);
      for (int s = 0; s < samples_per_pix; ++s) {
        float u = static_cast<float>(i + rdouble()) / static_cast<float>(nx);
        float v = static_cast<float>(j + rdouble()) / static_cast<float>(ny);
        Ray r = cam.getRay(u, 1 - v);
        col += color(r, *world, 0);
      }
      col /= static_cast<float>(samples_per_pix);
      col = sqrt(col);

      int ir = std::min(255, std::max(static_cast<int>(255.99 * col.r), 0));
      int ig = std::min(255, std::max(static_cast<int>(255.99 * col.g), 0));
      int ib = std::min(255, std::max(static_cast<int>(255.99 * col.b), 0));

      int pix_idx = j * nx + i;
      img_data.data[n_channels * pix_idx + 0] = ir;
      img_data.data[n_channels * pix_idx + 1] = ig;
      img_data.data[n_channels * pix_idx + 2] = ib;
    }
  }
}

vec3 BasicTracer::color(const Ray& r, const HitObject& world, int depth) const
{
  HitRecord rec;
  if (world.hit(r, {0.001f, std::numeric_limits<float>::max()}, rec)) {
    vec3 target = rec.p + rec.normal + runit_sphere();
    const Ray reflected = Ray(rec.p, target - rec.p);
    return 0.5f * color(reflected, world, depth - 1);
  }

  vec3 unit_dir = glm::normalize(r.direction());
  float t = 0.5f * (unit_dir.y + 1.f);
  return (1.f - t) * vec3(1.f) + t * vec3(0.5f, 0.7f, 1.f);
}

vec3 NormalTracer::color(const Ray& r, const HitObject& world, int depth) const
{
  HitRecord rec;
  if (world.hit(r, {0.001f, std::numeric_limits<float>::max()}, rec)) {
    return (0.5f * (rec.normal + 1.f));
  }

  vec3 unit_dir = glm::normalize(r.direction());
  float t = 0.5f * (unit_dir.y + 1.f);
  return (1.f - t) * vec3(1.f) + t * vec3(0.5f, 0.7f, 1.f);
}

vec3 LightTracer::color(const Ray& r, const HitObject& world, int depth) const
{
  HitRecord rec;
  if (world.hit(r, {0.001f, std::numeric_limits<float>::max()}, rec)) {
    Ray scattered;
    vec3 attenuation;
    vec3 emitted = rec.material->emit();

    if (depth < 50 && rec.material->scatter(r, rec, attenuation, scattered)) {
      return emitted + attenuation * color(scattered, world, depth + 1);
    }
    return emitted;
  }

  return vec3(0.f);
}
