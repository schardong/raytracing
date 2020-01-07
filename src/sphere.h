#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "hitobject.h"

class HitRecord;
class Material;
class Ray;

class Sphere: public HitObject
{
public:
  Sphere();
  Sphere(glm::vec3 center, float radius, Material* mat);
  virtual ~Sphere();

  virtual bool hit(const Ray& r, std::pair<float, float> t_lim,
                   HitRecord& rec) const;
  virtual bool bounding_box(AABB& box) const;

  const glm::vec3 center() const;
  const float radius() const;

private:
  glm::vec3 m_center;
  std::shared_ptr<Material> m_material;
  float m_radius;
};

#endif // SPHERE_H
