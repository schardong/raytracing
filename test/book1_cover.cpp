#include <iostream>
#include <memory>

#include "bvhnode.h"
#include "camera.h"
#include "geomgen.h"
#include "texture.h"
#include "material.h"
#include "sphere.h"
#include "trace.h"
#include "utils.h"

int main(int argc, char** argv)
{
  using namespace std;
  using namespace glm;

  int nx = 1200;
  int ny = 800;
  int n_samples = 500;

  if (argc > 1)
    nx = atoi(argv[1]);
  if (argc > 2)
    ny = atoi(argv[2]);
  if (argc > 3)
    n_samples = atoi(argv[3]);

  BVHNode* world = static_cast<BVHNode*>(book1_cover(true));

  vec3 pos = vec3(13.f, 2.f, 3.f);
  vec3 lookat = vec3(0.f, 0.f, 0.f);
  vec3 up = vec3(0.f, 1.f, 0.f);
  float aperture = 0.1f;
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

  ReflectionTracer t;
  t.trace(world, cam, img_data, n_samples);
  to_ppm({nx, ny}, 3, img_data.data);

  return 0;
}
