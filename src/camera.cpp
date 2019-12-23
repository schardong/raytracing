#include "camera.h"

using glm::vec3;

Camera::Camera() : m_ll_corner(vec3(-2.f, -1.f, -1.f)), m_origin(vec3(0.f)),
                   m_up(vec3(0.f, 2.f, 0.f)), m_right(vec3(4.f, 0.f, 0.f))
{}

Ray Camera::getRay(float u, float v)
{
  return Ray(m_origin, m_ll_corner + u * m_right + v * m_up - m_origin);
}
