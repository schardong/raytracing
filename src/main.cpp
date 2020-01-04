#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "aabb.h"
#include "bvhnode.h"
#include "camera.h"
#include "geomgen.h"
#include "hitrecord.h"
#include "hitobjectlist.h"
#include "material.h"
#include "ray.h"
#include "sphere.h"
#include "texture.h"
#include "utils.h"

using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using glm::vec3;

typedef struct
{
  int nx;
  int ny;
  int n_channels;
  std::vector<int> data;
} ImgData;

vec3 color(const Ray& r, const HitObject& world, int depth)
{
  HitRecord rec;
  if (world.hit(r, {0.001f, std::numeric_limits<float>::max()}, rec)) {
    Ray scattered;
    vec3 attenuation;
    vec3 emitted = rec.material->emit();

    if (depth < 50 && rec.material->scatter(r, rec, attenuation, scattered)) {
      return attenuation * color(scattered, world, depth + 1);
    }
    return emitted;
  }

  //  return vec3(0.f);

  vec3 unit_dir = glm::normalize(r.direction());
  float t = 0.5f * (unit_dir.y + 1.f);
  return (1.f - t) * vec3(1.f) + t * vec3(0.5f, 0.7f, 1.f);
}

void trace_full(HitObject* world, Camera& cam, ImgData& img_data,
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

      int ir = static_cast<int>(255.99 * col.r);
      int ig = static_cast<int>(255.99 * col.g);
      int ib = static_cast<int>(255.99 * col.b);

      int pix_idx = j * nx + i;
      img_data.data[n_channels * pix_idx + 0] = ir;
      img_data.data[n_channels * pix_idx + 1] = ig;
      img_data.data[n_channels * pix_idx + 2] = ib;
    }
  }
}

int main(int argc, char** argv)
{
  const int N_CHANNELS = 3;
  int nx = 200;
  int ny = 100;
  int n_samples = 100;

  if (argc > 1)
    nx = atoi(argv[1]);
  if (argc > 2)
    ny = atoi(argv[2]);
  if (argc > 3)
    n_samples = atoi(argv[3]);

  auto red = make_unique<ConstantTexture>(vec3(1.f, 0.f, 0.f));
  auto green = make_unique<ConstantTexture>(vec3(0.f, 1.f, 0.f));
  auto perlin = make_unique<PerlinTexture>();

  HitObject* ground = new Sphere(vec3(0.f, -1000.f, 0.f),
                                 1000.f,
                                 new Lambertian(std::move(perlin)));
  HitObject* ball = new Sphere(vec3(0.f, 1.f, 0.f),
                               1.f,
                               new Lambertian(std::move(green)));
  HitObject* sun = new Sphere(vec3(0.f, 2.f, 2.f),
                              0.2f,
                              new Lambertian(std::move(red)));

  HitObject* world = new BVHNode({ground, ball, sun});

  vec3 pos = vec3(13.f, 2.f, 3.f);
  vec3 lookat = vec3(0.f, 0.f, 0.f);
  vec3 up = vec3(0.f, 1.f, 0.f);
  float aperture = 0.0f;
  float dist_to_focus = 10.f;
  Camera cam(pos, lookat, up, 20, float(nx) / float(ny), aperture,
             dist_to_focus);
  vector<int> data;

  ImgData img_data = {
                      .nx = nx,
                      .ny = ny,
                      .n_channels = N_CHANNELS,
                      .data = data,
  };

  trace_full(world, cam, img_data, n_samples);
  to_ppm({nx, ny}, N_CHANNELS, img_data.data);

  return 0;
}
