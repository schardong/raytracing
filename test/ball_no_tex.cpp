#include <iostream>
#include <memory>

#include "bvhnode.h"
#include "camera.h"
#include "texture.h"
#include "material.h"
#include "sphere.h"
#include "trace.h"
#include "utils.h"

using std::vector;
using std::unique_ptr;
using std::make_unique;
using glm::vec3;

int main(int argc, char** argv)
{
  const int N_CHANNELS = 3;
  int nx = 800;
  int ny = 800;
  int n_samples = 300;

  if (argc > 1)
    nx = atoi(argv[1]);
  if (argc > 2)
    ny = atoi(argv[2]);
  if (argc > 3)
    n_samples = atoi(argv[3]);

  auto p0 = make_unique<ConstantTexture>(glm::vec3(0.8f));
  auto p1 = make_unique<ConstantTexture>(glm::vec3(0.9f));

  HitObject* ground = new Sphere(vec3(0.f, -100.5f, -1.f),
                                 100.f,
                                 new Lambertian(std::move(p0)));
  HitObject* ball = new Sphere(vec3(0.f, 0.f, -1.f),
                               0.5f,
                               new Lambertian(std::move(p1)));

  HitObject* world = new BVHNode({ground, ball});

  vec3 pos = vec3(0.f);
  vec3 lookat = vec3(0.f, 0.f, -1.f);
  vec3 up = vec3(0.f, 1.f, 0.f);
  float aperture = 0.0f;
  float dist_to_focus = 1.f;
  Camera cam(pos, lookat, up, 90, float(nx) / float(ny), aperture,
             dist_to_focus);

  vector<int> data;

  ImgData img_data = {
                      .nx = nx,
                      .ny = ny,
                      .n_channels = N_CHANNELS,
                      .data = data,
  };

  BasicTracer t;
  t.trace(world, cam, img_data, n_samples);
  to_ppm({nx, ny}, N_CHANNELS, img_data.data);

  return 0;
}
