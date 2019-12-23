#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class Camera
{
public:
  Camera();
  Ray getRay(float u, float v);

private:
  glm::vec3 m_origin;
  glm::vec3 m_ll_corner;
  glm::vec3 m_right;
  glm::vec3 m_up;
};

#endif // CAMERA_H
