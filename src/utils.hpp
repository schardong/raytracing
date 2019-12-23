#ifndef UTILS_HPP
#define UTILS_HPP

#include <functional>
#include <random>

inline double rdouble() {
  static std::uniform_real_distribution<double> dist(0.0, 1.0);
  static std::mt19937 generator;
  static std::function<double()> rand_generator = std::bind(dist, generator);
  return rand_generator();
}

inline glm::vec3 runit_sphere()
{
  using glm::vec3;
  using glm::dot;

  vec3 p;
  do {
    p = 2.f * vec3(rdouble(), rdouble(), rdouble()) - vec3(1.f);
  } while (dot(p, p) >= 1.f);
  return p;
}

#endif // UTILS_HPP
