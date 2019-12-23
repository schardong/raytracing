#include "material.h"
#include "hitrecord.h"
#include "ray.h"
#include "utils.hpp"

Lambertian::Lambertian(glm::vec3 albedo) : m_albedo(albedo) {}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec,
                         glm::vec3& attenuation, Ray& scattered) const
{
  glm::vec3 target = rec.p + rec.normal + runit_sphere();
  scattered = Ray(rec.p, target - rec.p);
  attenuation = m_albedo;
  return true;
}
