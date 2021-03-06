#include "ray.h"

Ray::Ray() {}

Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction) :
  m_origin(origin), m_direction(direction)
{}

glm::vec3 Ray::origin() const { return m_origin; }

glm::vec3 Ray::direction() const { return m_direction; }

glm::vec3 Ray::p(const float t) const { return origin() + t * direction(); }

std::ostream& operator<<(std::ostream& os, const Ray& r)
{
  os << "o: [" << r.origin().x << ", " << r.origin().y << ", " << r.origin().z << "]";
  os << ", d: [" << r.direction().x << ", " << r.direction().y << ", " <<  r.direction().z << "]";
  return os;
}
