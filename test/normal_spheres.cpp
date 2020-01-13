#include <iostream>
#include <memory>

#include "bvhnode.h"
#include "camera.h"
#include "texture.h"
#include "material.h"
#include "sphere.h"
#include "trace.h"
#include "utils.h"

int main()
{
  using namespace std;
  using namespace glm;

  const int nx = 200;
  const int ny = 200;
  const int n_samples = 100;

  auto p0 = make_unique<ConstantTexture>(glm::vec3(0.8f));
  auto p1 = make_unique<ConstantTexture>(glm::vec3(0.9f));

  HitObject* ground = new Sphere(vec3(0.f, -100.f, -2.f),
                                 100.f,
                                 new Lambertian(std::move(p0)));
  HitObject* ball = new Sphere(vec3(0.f, 1.f, -2.f),
                               1.f,
                               new Lambertian(std::move(p1)));
  HitObject* world = new BVHNode({ground, ball});

  vec3 pos = vec3(0.f);
  vec3 lookat = vec3(0.f, 0.f, -1.f);
  vec3 up = vec3(0.f, 1.f, 0.f);
  float aperture = 0.f;
  float dist_to_focus = 1.f;
  Camera cam(pos, lookat, up, 90, float(nx) / float(ny), aperture,
             dist_to_focus);

  vector<int> data;

  ImgData img_data = {
                      .nx = nx,
                      .ny = ny,
                      .n_channels = 3,
                      .data = data,
  };

  NormalTracer t;
  t.trace(world, cam, img_data, 3);
  to_ppm({nx, ny}, 3, img_data.data);

  return 0;
}
