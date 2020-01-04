#include "texture.h"
#include "utils.h"

#include <algorithm>
#include <random>
#include <vector>

void generate_seed(std::vector<float>& seed)
{
  seed.resize(256);
  for (auto& s : seed)
    s = static_cast<float>(rdouble());
}

class PerlinGenerator
{
public:
  PerlinGenerator();
  ~PerlinGenerator() = default;
  float noise(glm::vec3 p);

private:
  std::vector<float> m_randfloat;
  std::vector<int> m_permx;
  std::vector<int> m_permy;
  std::vector<int> m_permz;
};

PerlinGenerator::PerlinGenerator()
{
  generate_seed(m_randfloat);
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

float PerlinGenerator::noise(glm::vec3 p)
{
  int i = static_cast<int>(std::floor(std::abs(p.x)));
  int j = static_cast<int>(std::floor(std::abs(p.y)));
  int k = static_cast<int>(std::floor(std::abs(p.z)));

  float c[2][2][2];
  for (int di = 0; di < 2; ++di)
    for (int dj = 0; dj < 2; ++dj)
      for (int dk = 0; dk < 2; ++dk)
        c[di][dj][dk] = m_randfloat[m_permx[i+di] ^ m_permy[j+dj] ^ m_permz[k+dk]];

  float u = std::abs(p.x) - static_cast<float>(i);
  float v = std::abs(p.y) - static_cast<float>(j);
  float w = std::abs(p.z) - static_cast<float>(k);

  u = u * u * (3 - 2 * u);
  v = v * v * (3 - 2 * v);
  w = w * w * (3 - 2 * w);

  return trilinear_interp(c, {u, v, w});
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
  float n = m_noisegen->noise(m_scale * p);
  return glm::vec3(1.f) * n;
}
