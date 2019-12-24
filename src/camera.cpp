#include "camera.h"

#define _USE_MATH_DEFINES
#include <cmath>

using glm::vec3;
using glm::dot;
using glm::cross;
using glm::normalize;

Camera::Camera(vec3 pos, vec3 lookat, vec3 up, float vfov, float aspect)
{
  float theta = vfov * M_PI / 180.f;
  float half_height = tan(theta / 2.f);
  float half_width = aspect * half_height;
  vec3 u, v, w;

  m_origin = pos;
  w = normalize(pos - lookat);
  u = normalize(cross(up, w));
  v = cross(w, u);

  m_ll_corner = pos - half_width * u - half_height * v - w;
  m_right = 2 * half_width * u;
  m_up = 2 * half_height * v;
}

Ray Camera::getRay(float u, float v)
{
  return Ray(m_origin, m_ll_corner + u * m_right + v * m_up - m_origin);
}
