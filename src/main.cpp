#include <iostream>
#include <cstdlib>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "std_image.h"

extern "C" {
#include "stb_image_write.h"
}

#include "ray.h"

glm::vec3 color(const Ray& r)
{
  glm::vec3 unit_dir = glm::normalize(r.direction());
  float t = 0.5f * (unit_dir.y + 1.0f);
  return (1.f - t) * glm::vec3(1.f) + t * glm::vec3(0.3f, 0.7f, 1.f);
}

int main(int argc, char** argv)
{
  int nx = 400;
  int ny = 200;
  int n_samples = 400;

  if (argc > 1)
    nx = atoi(argv[1]);
  if (argc > 2)
    ny = atoi(argv[2]);
  if (argc > 3)
    n_samples = atoi(argv[3]);

  glm::vec3 origin(0.f);
  glm::vec3 ll_corner(-2.f, -1.f, -1.f);
  glm::vec3 horizontal(4.f, 0.f, 0.f);
  glm::vec3 vertical(0.f, 2.f, 0.f);

  std::vector<uint8_t> img_data(nx * ny * 4);
  for (int j = ny-1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      float u = static_cast<float>(i) / static_cast<float>(nx);
      float v = static_cast<float>(j) / static_cast<float>(ny);
      Ray r(origin, ll_corner + u * horizontal + v * vertical);

      glm::vec3 c = color(r);
    }
  }

  char fname[256] = "image.png";
  if (argc > 4)
    strcpy(fname, argv[4]);

  stbi_write_png(fname, nx, ny, 4, img_data.data(), 0);

  return 0;
}
