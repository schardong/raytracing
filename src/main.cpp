#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "camera.h"
#include "material.h"
#include "hitrecord.h"
#include "hitobjectlist.h"
#include "ray.h"
#include "sphere.h"
#include "utils.hpp"

using std::cout;
using std::endl;
using std::vector;
using glm::vec3;

vec3 color(const Ray& r, const HitObject& world, int depth)
{
  HitRecord rec;
  if (world.hit(r, {0.001f, std::numeric_limits<float>::max()}, rec)) {
    Ray scattered;
    vec3 attenuation;

    if (depth < 50 && rec.material->scatter(r, rec, attenuation, scattered)) {
      return attenuation * color(scattered, world, depth + 1);
    } else {
      return vec3(0.f);
    }
  }

  vec3 unit_dir = glm::normalize(r.direction());
  float t = 0.5f * (unit_dir.y + 1.f);
  return (1.f - t) * vec3(1.f) + t * vec3(0.5f, 0.7f, 1.f);
}

HitObject* random_spheres()
{
  HitObjectList* world = new HitObjectList;
  world->pushObject(new Sphere(vec3(0.f, -1000.f, 0.f), 1000.f, new Lambertian(vec3(0.5f))));

  for(int a = -11; a < 11; ++a) {
    for (int b = -11; b < 11; ++b) {
      float mat_prob = rdouble();
      vec3 center = vec3(a + 0.9f * rdouble(), 0.2f, b + 0.9f * rdouble());
      Material* mat;
      if ((center - vec3(4.f, 0.2f, 0.f)).length() > 0.9f) {
        if (mat_prob < 0.8f) {
          mat = new Lambertian(vec3(rdouble() * rdouble(),
                                    rdouble() * rdouble(),
                                    rdouble() * rdouble()));
        } else if (mat_prob < 0.95f) {
          mat = new Metal(vec3(0.5f * (1 + rdouble()),
                               0.5f * (1 + rdouble()),
                               0.5f * (1 + rdouble())),
                          0.5f * rdouble());
        } else {
          mat = new Dielectric(1.5f);
        }
        world->pushObject(new Sphere(center, 0.2f, mat));
      }
    }
  }

  world->pushObject(new Sphere(vec3(0.f, 1.f, 0.f), 1.f, new Dielectric(1.5f)));
  world->pushObject(new Sphere(vec3(-4.f, 1.f, 0.f), 1.f,
                               new Lambertian(vec3(0.4f, 0.2f, 0.1f))));
  world->pushObject(new Sphere(vec3(4.f, 1.f, 0.f), 1.f,
                               new Metal(vec3(0.7f, 0.6f, 0.5f), 0.f)));
  return world;
}

void to_ppm(const std::vector<int>& data, size_t w, size_t h, size_t n_channels=3)
{
  cout << "P3\n" << w << " " << h << "\n255" << endl;
  for (size_t i = 0; i < data.size(); i += n_channels) {
    for (size_t c = 0; c < n_channels; ++c)
      cout << data[i+c] << " ";
    cout << endl;
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

  HitObject* world = random_spheres();

  vec3 pos = vec3(13.f, 2.f, 3.f);
  vec3 lookat = vec3(0.f, 0.f, 0.f);
  vec3 up = vec3(0.f, 1.f, 0.f);
  float aperture = 0.1f;
  float dist_to_focus = 10.f;
  Camera cam(pos, lookat, up, 20, float(nx) / float(ny), aperture, dist_to_focus);
  vector<int> img_data(nx * ny * N_CHANNELS);

  for (int j = ny-1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      vec3 col(0.f);
      for (int s = 0; s < n_samples; ++s) {
        float u = static_cast<float>(i + rdouble()) / static_cast<float>(nx);
        float v = static_cast<float>(j + rdouble()) / static_cast<float>(ny);
        Ray r = cam.getRay(u, 1 - v);
        col += color(r, *world, 0);
      }
      col /= static_cast<float>(n_samples);
      col = sqrt(col);

      int ir = static_cast<int>(255.99 * col.r);
      int ig = static_cast<int>(255.99 * col.g);
      int ib = static_cast<int>(255.99 * col.b);

      int pix_idx = j * nx + i;
      img_data[N_CHANNELS * pix_idx + 0] = ir;
      img_data[N_CHANNELS * pix_idx + 1] = ig;
      img_data[N_CHANNELS * pix_idx + 2] = ib;
    }
  }

  to_ppm(img_data, nx, ny, N_CHANNELS);

  delete world;
  return 0;
}
