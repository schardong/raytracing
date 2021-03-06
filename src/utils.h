#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

typedef struct
{
  int nx;
  int ny;
  int n_channels;
  std::vector<int> data;
} ImgData;

double rdouble();

glm::vec3 runit_sphere();

glm::vec3 runit_disc();

glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n);

bool refract(glm::vec3 v, glm::vec3 n, float ni_over_nt, glm::vec3& refracted);

void to_ppm(std::pair<int, int> img_dims, int n_channels,
            std::vector<int>& img_data);

float trilinear_interp(float c[2][2][2], std::tuple<float, float, float> uvw);

#endif // UTILS_H
