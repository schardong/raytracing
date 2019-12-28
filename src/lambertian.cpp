#include "material.h"
#include "hitrecord.h"
#include "ray.h"
#include "texture.h"
#include "utils.hpp"

Lambertian::Lambertian(std::unique_ptr<Texture> albedo) :
  m_albedo(std::move(albedo))
{}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec,
                         glm::vec3& attenuation, Ray& scattered) const
{
  glm::vec3 target = rec.p + rec.normal + runit_sphere();
  scattered = Ray(rec.p, target - rec.p);
  attenuation = m_albedo->value({0.f, 0.f}, rec.p);
  return true;
}
