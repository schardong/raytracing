#include "geomgen.h"
#include "bvhnode.h"
#include "hitobject.h"
#include "hitobjectlist.h"
#include "material.h"
#include "sphere.h"
#include "texture.h"
#include "utils.h"

#include <memory>
#include <vector>

using std::vector;
using std::unique_ptr;
using std::make_unique;
using glm::vec3;

HitObject* book1_cover(bool with_bvh)
{
  typedef ConstantTexture CT;
  typedef CheckersTexture CHKT;

  vector<HitObject*> objs;

  auto checkers = make_unique<CheckersTexture>(make_unique<CT>(vec3(0.2f, 0.3f, 0.1f)),
                                               make_unique<CT>(vec3(0.9f)));

  objs.push_back(new Sphere(vec3(0.f, -1000.f, 0.f),
                            1000.f,
                            new Lambertian(std::move(checkers))));

  for(int a = -11; a < 11; ++a) {
    for (int b = -11; b < 11; ++b) {
      float mat_prob = rdouble();
      vec3 center = vec3(a + 0.9f * rdouble(), 0.2f, b + 0.9f * rdouble());
      Material* mat;
      if ((center - vec3(4.f, 0.2f, 0.f)).length() > 0.9f) {
        if (mat_prob < 0.8f) {
          auto t = make_unique<CT>(vec3(rdouble() * rdouble(),
                                        rdouble() * rdouble(),
                                        rdouble() * rdouble()));
          mat = new Lambertian(std::move(t));
        } else if (mat_prob < 0.95f) {
          mat = new Metal(vec3(0.5f * (1 + rdouble()),
                               0.5f * (1 + rdouble()),
                               0.5f * (1 + rdouble())),
                          0.5f * rdouble());
        } else {
          mat = new Dielectric(1.5f);
        }
        objs.push_back(new Sphere(center, 0.2f, mat));
      }
    }
  }

  objs.push_back(new Sphere(vec3(0.f, 1.f, 0.f), 1.f, new Dielectric(1.5f)));
  objs.push_back(new Sphere(vec3(-4.f, 1.f, 0.f),
                            1.f,
                            new Lambertian(make_unique<CT>(vec3(0.4f, 0.2f, 0.1f)))));
  objs.push_back(new Sphere(vec3(4.f, 1.f, 0.f), 1.f,
                               new Metal(vec3(0.7f, 0.6f, 0.5f), 0.f)));

  if (with_bvh) {
    BVHNode* root = new BVHNode(objs);
    return root;
  }

  HitObjectList* world = new HitObjectList(objs);
  return world;
}

HitObject* two_spheres_turbulence()
{
  //texture *pertext = new noise_texture();
  auto red = make_unique<ConstantTexture>(vec3(1.f, 0.f, 0.f));
  auto green = make_unique<ConstantTexture>(vec3(0.f, 1.f, 0.f));

  vector<HitObject*> objs;
  objs.push_back(new Sphere(vec3(0,-1000, 0), 1000, new Lambertian(std::move(red))));
  objs.push_back(new Sphere(vec3(0, 2, 0), 2, new Lambertian(std::move(green))));

  HitObjectList* world = new HitObjectList(objs);
  return world;
}
