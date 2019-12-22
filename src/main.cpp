#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

/*
#define STB_IMAGE_IMPLEMENTATION
extern "C" {
#include "stb_image.h"
#include "stb_image_write.h"
}
*/

#include "ray.h"

glm::vec3 color(const Ray& r)
{
  glm::vec3 unit_dir = glm::normalize(r.direction());
  float t = 0.5f * (unit_dir.y + 1.0f);
  return (1.f - t) * glm::vec3(1.f) + t * glm::vec3(0.3f, 0.7f, 1.f);
}

void to_ppm(const std::vector<int>& data, size_t w, size_t h, size_t n_channels=3)
{
  std::cout << "P3\n" << w << " " << h << "\n255\n";
  for (size_t i = 0; i < data.size(); i += n_channels) {
    for (size_t c = 0; c < n_channels; ++c)
      std::cout << data[i+c] << " ";
    std::cout << std::endl;
  }
}

int main(int argc, char** argv)
{
  const int N_CHANNELS = 3;
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

  std::vector<int> img_data(nx * ny * N_CHANNELS);
  for (int j = ny-1; j >= 0; --j) {
    for (int i = 0; i < nx; ++i) {
      float u = static_cast<float>(i) / static_cast<float>(nx);
      float v = static_cast<float>(j) / static_cast<float>(ny);

      Ray r(origin, ll_corner + u * horizontal + v * vertical);

      glm::vec3 col = color(r);
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

  /*
  char fname[256] = "image.png";
  if (argc > 4)
    strcpy(fname, argv[4]);

  stbi_write_png(fname, nx, ny, 4, img_data.data(), 0);
  */
  return 0;
}
