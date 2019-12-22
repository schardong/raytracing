#ifndef RAY_H
#define RAY_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class Ray
{
public:
  Ray();
  Ray(const glm::vec3& origin, const glm::vec3& direction);
  glm::vec3 origin() const;
  glm::vec3 direction() const;
  glm::vec3 p(const float t) const;

private:
  glm::vec3 m_origin;
  glm::vec3 m_direction;
};

#endif /* RAY_H */
