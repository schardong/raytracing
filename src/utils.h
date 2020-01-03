#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

double rdouble();

glm::vec3 runit_sphere();

glm::vec3 runit_disc();

glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n);

bool refract(glm::vec3 v, glm::vec3 n, float ni_over_nt, glm::vec3& refracted);

void to_ppm(std::pair<int, int> img_dims, int n_channels,
            std::vector<int>& img_data);

#endif // UTILS_HPP
