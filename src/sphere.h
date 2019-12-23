#ifndef SPHERE_H
#define SPHERE_H

#include "hitobject.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class HitRecord;
class Ray;

class Sphere: public HitObject
{
public:
  Sphere();
  Sphere(glm::vec3 center, float radius);
  virtual bool hit(const Ray& r, std::pair<float, float> t_lim,
                   HitRecord& rec) const;

private:
  glm::vec3 m_center;
  float m_radius;
};

#endif // SPHERE_H
