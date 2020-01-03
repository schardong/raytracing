#include "texture.h"
#include "utils.h"

#include <algorithm>
#include <random>
#include <vector>

void generate_seed(std::vector<float>& seed)
{
  seed.resize(256);
  for (auto& s : seed)
    s = rdouble();
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

PerlinTexture::PerlinTexture()
{
  m_noisegen = std::make_unique<PerlinGenerator>();
}

PerlinTexture::~PerlinTexture()
{}

glm::vec3 PerlinTexture::value(std::pair<float, float> uv, glm::vec3 p) const
{
  return glm::vec3(1.f) * m_noisegen->noise(p);
}

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
  int i = std::floor(std::abs(p.x));
  int j = std::floor(std::abs(p.y));
  int k = std::floor(std::abs(p.z));
  return m_randfloat[m_permx[i] ^ m_permy[j] ^ m_permz[k]];
}
