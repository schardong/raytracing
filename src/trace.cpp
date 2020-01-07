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

vec3 color(const Ray& r, const HitObject& world, int depth)
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

void trace(HitObject* world, Camera& cam, ImgData& img_data,
           int samples_per_pix)
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

      int ir = std::clamp(static_cast<int>(255.99 * col.r), 0, 255);
      int ig = std::clamp(static_cast<int>(255.99 * col.g), 0, 255);
      int ib = std::clamp(static_cast<int>(255.99 * col.b), 0, 255);

      int pix_idx = j * nx + i;
      img_data.data[n_channels * pix_idx + 0] = ir;
      img_data.data[n_channels * pix_idx + 1] = ig;
      img_data.data[n_channels * pix_idx + 2] = ib;
    }
  }
}
