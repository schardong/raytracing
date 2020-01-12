#ifndef HITRECORD_H
#define HITRECORD_H

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class Material;

struct HitRecord
{
  float t;
  glm::vec3 p;
  glm::vec3 normal;
  std::shared_ptr<Material> material;
};

#endif // HITRECORD_H
