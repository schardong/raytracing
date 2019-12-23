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

#endif // UTILS_HPP
