#include "texture.h"

ConstantTexture::ConstantTexture(glm::vec3 rgb) :
  m_color(rgb)
{}

ConstantTexture::~ConstantTexture()
{}

glm::vec3 ConstantTexture::value(std::pair<float, float> uv, glm::vec3 p) const
{
  return m_color;
}
