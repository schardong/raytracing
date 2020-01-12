#ifndef AABB_H
#define AABB_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class Ray;

class AABB
{
public:
  AABB() = default;
  AABB(glm::vec3 x1, glm::vec3 x2);
  AABB(AABB box0, AABB box1);

  glm::vec3 bottom() const;
  glm::vec3 top() const;

  bool hit(const Ray& r_in, std::pair<float, float> t_lim) const;

private:
  glm::vec3 m_min;
  glm::vec3 m_max;
};

#endif // AABB_H
