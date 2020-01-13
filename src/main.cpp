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
#include "rect.h"
#include "sphere.h"
#include "texture.h"
#include "trace.h"
#include "utils.h"

using std::vector;
using std::unique_ptr;
using std::make_unique;
using glm::vec3;

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

  auto light = new DiffuseLight(vec3(4.f));
  auto light2 = new DiffuseLight(vec3(5.f, 2.f, 2.f));
  auto p0 = make_unique<PerlinTexture>(5.f);
  auto p1 = make_unique<PerlinTexture>(4.f);

  HitObject* ground = new Sphere(vec3(0.f, -1000.f, 0.f),
                                 1000.f,
                                 new Lambertian(std::move(p0)));
  HitObject* ball = new Sphere(vec3(0.f, 1.f, 3.f),
                               1.f,
                               new Lambertian(std::move(p1)));
  HitObject* sun = new Sphere(vec3(0.f, 4.f, 3.f),
                              1.f,
                              light);
  HitObject* wall_light = new Rect(glm::vec2(-1.f, 0.f), {2, 2}, light2);

  HitObject* world = new BVHNode({ground, ball, sun, wall_light});

  vec3 pos = vec3(13.f, 2.f, 3.f);
  vec3 lookat = vec3(0.f, 0.f, 3.f);
  vec3 up = vec3(0.f, 1.f, 0.f);
  float aperture = 0.0f;
  float dist_to_focus = 10.f;
  Camera cam(pos, lookat, up, 45, float(nx) / float(ny), aperture,
             dist_to_focus);
  vector<int> data;

  ImgData img_data = {
                      .nx = nx,
                      .ny = ny,
                      .n_channels = N_CHANNELS,
                      .data = data,
  };

  LightTracer t;
  t.trace(world, cam, img_data, n_samples);
  to_ppm({nx, ny}, N_CHANNELS, img_data.data);

  return 0;
}
