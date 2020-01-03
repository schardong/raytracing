#include "utils.h"

#include <iostream>
#include <functional>
#include <random>

using glm::vec3;
using glm::dot;
using glm::normalize;

double rdouble() {
  static std::uniform_real_distribution<double> dist(0.0, 1.0);
  static std::mt19937 generator;
  static std::function<double()> rand_generator = std::bind(dist, generator);
  return rand_generator();
}

vec3 runit_sphere()
{
  vec3 p;
  do {
    p = 2.f * vec3(rdouble(), rdouble(), rdouble()) - vec3(1.f);
  } while (dot(p, p) >= 1.f);
  return p;
}

vec3 runit_disc()
{
  vec3 p;
  do {
    p = 2.f * vec3(rdouble(), rdouble(), 0.f) - vec3(1.f, 1.f, 0.f);
  } while (dot(p, p) >= 1.f);
  return p;
}

vec3 reflect(const vec3& v, const vec3& n)
{
  return v - 2 * dot(v, n) * n;
}

bool refract(vec3 v, vec3 n, float ni_over_nt, vec3& refracted)
{
  vec3 uv = normalize(v);
  float dt = dot(uv, n);
  float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);
  if (discriminant > 0) {
    refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
    return true;
  }
  return false;
}

void to_ppm(std::pair<int, int> img_dims, int n_channels,
            std::vector<int>& img_data)
{
  using std::cout;
  using std::endl;

  if (img_data.empty()) {
    throw std::runtime_error("No valid image data found.");
    return;
  }

  int nx = img_dims.first;
  int ny = img_dims.second;

  cout << "P3\n" << nx << " " << ny << "\n255" << endl;
  for (size_t i = 0; i < img_data.size(); i += n_channels) {
    for (size_t c = 0; c < n_channels; ++c)
      cout << img_data[i + c] << " ";
    cout << endl;
  }
}
