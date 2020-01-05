#include "texture.h"
#include "utils.h"

#include <algorithm>
#include <random>
#include <vector>

void generate_seed(std::vector<glm::vec3>& seed)
{
  seed.resize(256);
  for (auto& s : seed) {
    s = glm::vec3(2 * rdouble() - 1,
                  2 * rdouble() - 1,
                  2 * rdouble() - 1);
    s = glm::normalize(s);
  }
}

float perlin_trilinear(glm::vec3 c[2][2][2], std::tuple<float, float, float> uvw)
{
  float acc = 0.f;
  float u = std::get<0>(uvw);
  float v = std::get<1>(uvw);
  float w = std::get<2>(uvw);

  float uu = u * u * (3 - 2 * u);
  float vv = v * v * (3 - 2 * v);
  float ww = w * w * (3 - 2 * w);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      for (int k = 0; k < 2; ++k) {
        glm::vec3 weight = glm::vec3(u - i, v - j, w - k);
        acc +=
          (i * uu + (1 - i) * (1 - uu)) *
          (j * vv + (1 - j) * (1 - vv)) *
          (k * ww + (1 - k) * (1 - ww)) *
          glm::dot(c[i][j][k], weight);
      }
    }
  }
  return acc;
}

class PerlinGenerator
{
public:
  PerlinGenerator();
  ~PerlinGenerator() = default;
  float noise(glm::vec3 p) const;
  float turbulence(glm::vec3 p, size_t depth=7) const;

private:
  std::vector<glm::vec3> m_randseed;
  std::vector<int> m_permx;
  std::vector<int> m_permy;
  std::vector<int> m_permz;
};

PerlinGenerator::PerlinGenerator()
{
  generate_seed(m_randseed);
  m_permx.resize(256);
  m_permy.resize(256);
  m_permz.resize(256);

  for (int i = 0; i < 256; ++i) {
    m_permx[i] = i;
    m_permy[i] = i;
    m_permz[i] = i;
  }

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(m_permx.begin(), m_permx.end(), g);
  std::shuffle(m_permy.begin(), m_permy.end(), g);
  std::shuffle(m_permz.begin(), m_permz.end(), g);
}

float PerlinGenerator::noise(glm::vec3 p) const
{
  int i = static_cast<int>(std::floor(std::abs(p.x)));
  int j = static_cast<int>(std::floor(std::abs(p.y)));
  int k = static_cast<int>(std::floor(std::abs(p.z)));

  glm::vec3 c[2][2][2];
  for (int di = 0; di < 2; ++di)
    for (int dj = 0; dj < 2; ++dj)
      for (int dk = 0; dk < 2; ++dk)
        c[di][dj][dk] = m_randseed[m_permx[(i + di) & 255] ^
                                   m_permy[(j + dj) & 255] ^
                                   m_permz[(k + dk) & 255]];

  float u = std::abs(p.x) - static_cast<float>(i);
  float v = std::abs(p.y) - static_cast<float>(j);
  float w = std::abs(p.z) - static_cast<float>(k);

  return perlin_trilinear(c, {u, v, w});
}

float PerlinGenerator::turbulence(glm::vec3 p, size_t depth) const
{
  glm::vec3 temp_p = p;
  float acc = 0.f;
  float weight = 1.f;

  for (size_t i = 0; i < depth; ++i) {
    acc += weight * noise(temp_p);
    weight *= 0.5f;
    temp_p *= 2.f;
  }

  return std::abs(acc);
}

/* Exported methods */
PerlinTexture::PerlinTexture() :
  m_scale(1.f)
{
  m_noisegen = std::make_unique<PerlinGenerator>();
}

PerlinTexture::PerlinTexture(float scale) :
  m_scale(scale)
{
  m_noisegen = std::make_unique<PerlinGenerator>();
}

PerlinTexture::~PerlinTexture()
{
  m_noisegen.reset(nullptr);
}

glm::vec3 PerlinTexture::value(std::pair<float, float> uv, glm::vec3 p) const
{
  float t = m_noisegen->turbulence(p);
  return glm::vec3(1.f) * 0.5f * (1 + sin(m_scale * p.z + 10.f * t));
}
