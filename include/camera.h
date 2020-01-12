#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class Camera
{
public:
  Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up, float vfov,
         float aspect, float aperture, float focus_disc);
  Ray getRay(float u, float v);

private:
  float m_lens_radius;
  glm::vec3 m_origin;
  glm::vec3 m_ll_corner;
  glm::vec3 m_right;
  glm::vec3 m_up;
  glm::vec3 m_u;
  glm::vec3 m_v;
  glm::vec3 m_w;
};

#endif // CAMERA_H
