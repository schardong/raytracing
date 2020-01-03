#include "camera.h"
#include "utils.h"

#define _USE_MATH_DEFINES
#include <cmath>

using glm::vec3;
using glm::dot;
using glm::cross;
using glm::normalize;

Camera::Camera(vec3 pos, vec3 lookat, vec3 up, float vfov, float aspect,
               float aperture, float focus_dist)
{
  m_lens_radius = aperture / 2.0f;
  float theta = vfov * M_PI / 180.0f;
  float half_height = tan(theta / 2.0f);
  float half_width = aspect * half_height;

  m_origin = pos;
  m_w = normalize(pos - lookat);
  m_u = normalize(cross(up, m_w));
  m_v = cross(m_w, m_u);

  m_ll_corner = pos -
    half_width * focus_dist * m_u -
    half_height * focus_dist * m_v -
    focus_dist * m_w;

  m_right = 2 * half_width * focus_dist * m_u;
  m_up = 2 * half_height * focus_dist * m_v;
}

Ray Camera::getRay(float u, float v)
{
  vec3 rd = m_lens_radius * runit_disc();
  vec3 off = rd.x * m_u + rd.y * m_v;
  return Ray(m_origin + off,
             m_ll_corner + u * m_right + v * m_up - m_origin - off);
}
