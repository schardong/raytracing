#include "material.h"
#include "hitrecord.h"
#include "ray.h"
#include "texture.h"

using glm::vec3;

DiffuseLight::DiffuseLight(vec3 color) : m_color(color) {
  float a = 0.f;
}

bool DiffuseLight::scatter(const Ray& r_in, const HitRecord& rec,
                           glm::vec3& attenuation, Ray& scattered) const
{
  return false;
}

glm::vec3 DiffuseLight::emit() const
{
  return m_color;
}
