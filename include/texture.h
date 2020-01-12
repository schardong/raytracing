#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class PerlinGenerator;

class Texture
{
public:
  virtual ~Texture() {}
  virtual glm::vec3 value(std::pair<float, float> uv, glm::vec3 p) const = 0;
};

class ConstantTexture: public Texture
{
public:
  ConstantTexture() = default;
  ConstantTexture(glm::vec3 rgb);
  virtual ~ConstantTexture();
  virtual glm::vec3 value(std::pair<float, float> uv, glm::vec3 p) const;

private:
  glm::vec3 m_color;
};

class CheckersTexture: public Texture
{
public:
  CheckersTexture() = default;
  CheckersTexture(std::unique_ptr<Texture> even, std::unique_ptr<Texture> odd);
  virtual ~CheckersTexture();
  virtual glm::vec3 value(std::pair<float, float> uv, glm::vec3 p) const;

private:
  std::unique_ptr<Texture> m_even;
  std::unique_ptr<Texture> m_odd;
};

class PerlinTexture: public Texture
{
public:
  PerlinTexture();
  PerlinTexture(float scale);
  virtual ~PerlinTexture();
  virtual glm::vec3 value(std::pair<float, float> uv, glm::vec3 p) const;

private:
  std::unique_ptr<PerlinGenerator> m_noisegen;
  float m_scale;
};

#endif // TEXTURE_H
