#include "texture.h"

CheckersTexture::CheckersTexture(std::unique_ptr<Texture> even, std::unique_ptr<Texture> odd)
{
  m_even = std::move(even);
  m_odd = std::move(odd);
}

CheckersTexture::~CheckersTexture()
{
  m_even.reset(nullptr);
  m_odd.reset(nullptr);
}

glm::vec3 CheckersTexture::value(std::pair<float, float> uv, glm::vec3 p) const
{
  float s = sin(10.f * p.x) * sin(10.f * p.y) * sin(10.f * p.z);
  if (s < 0)
    return m_odd->value(uv, p);
  return m_even->value(uv, p);
}
