#include "camera.h"

#define _USE_MATH_DEFINES
#include <cmath>

using glm::vec3;

Camera::Camera(float vfov, float aspect) : m_origin(vec3(0.f))
{
  float theta = vfov * M_PI / 180.f;
  float half_height = tan(theta / 2.f);
  float half_width = aspect * half_height;

  m_ll_corner = vec3(-half_width, -half_height, -1.0f);
  m_up = vec3(0.0f, 2 * half_height, 0.0f);
  m_right = vec3(2 * half_width, 0.0f, 0.0f);
}

Ray Camera::getRay(float u, float v)
{
  return Ray(m_origin, m_ll_corner + u * m_right + v * m_up - m_origin);
}
