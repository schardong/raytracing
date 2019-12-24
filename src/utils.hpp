#ifndef UTILS_HPP
#define UTILS_HPP

#include <functional>
#include <random>

using glm::vec3;
using glm::dot;
using glm::normalize;

inline double rdouble() {
  static std::uniform_real_distribution<double> dist(0.0, 1.0);
  static std::mt19937 generator;
  static std::function<double()> rand_generator = std::bind(dist, generator);
  return rand_generator();
}

inline vec3 runit_sphere()
{
  vec3 p;
  do {
    p = 2.f * vec3(rdouble(), rdouble(), rdouble()) - vec3(1.f);
  } while (dot(p, p) >= 1.f);
  return p;
}

inline vec3 reflect(const vec3& v, const vec3& n)
{
  return v - 2 * dot(v, n) * n;
}

inline bool refract(vec3 v, vec3 n, float ni_over_nt, vec3& refracted)
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

#endif // UTILS_HPP
