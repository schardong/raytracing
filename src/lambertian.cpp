#include "material.h"
#include "hitrecord.h"
#include "ray.h"
#include "texture.h"
#include "utils.h"

Lambertian::Lambertian(std::unique_ptr<Texture> albedo) :
  m_albedo(std::move(albedo))
{}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec,
                         glm::vec3& attenuation, Ray& scattered) const
{
  glm::vec3 target = rec.normal + runit_sphere();

  if (glm::length(target) < 1e-8)
    target = rec.normal;

  scattered = Ray(rec.p, target);
  attenuation = m_albedo->value({0.f, 0.f}, rec.p);
  return true;
}
