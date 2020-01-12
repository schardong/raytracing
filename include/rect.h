#ifndef RECT_H
#define RECT_H

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "hitobject.h"

class HitRecord;
class Material;
class Ray;

class Rect : public HitObject
{
public:
  Rect();
  Rect(glm::vec2 origin, std::pair<float, float> width_height, Material* mat,
       bool flip_normal=false);
  virtual ~Rect();

  virtual bool hit(const Ray& r, std::pair<float, float> t_lims,
                   HitRecord& rec) const;
  virtual bool bounding_box(AABB& box) const;

private:
  std::shared_ptr<Material> m_material;
  glm::vec3 m_bl;
  glm::vec3 m_tr;
  bool m_flip_normal;
};

#endif // RECT_H
