#ifndef HITRECORD_H
#define HITRECORD_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

struct HitRecord
{
  float t;
  glm::vec3 p;
  glm::vec3 normal;
};

#endif // HITRECORD_H
