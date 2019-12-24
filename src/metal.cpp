#include "material.h"
#include "hitrecord.h"
#include "ray.h"
#include "utils.hpp"

Metal::Metal(glm::vec3 albedo, float fuzz) : m_albedo(albedo)
{
  m_fuzz = std::clamp(fuzz, 0.f, 1.f);
}

bool Metal::scatter(const Ray& r_in, const HitRecord& rec,
                    glm::vec3& attenuation, Ray& scattered) const
{
  glm::vec3 reflected = reflect(glm::normalize(r_in.direction()), rec.normal);
  scattered = Ray(rec.p, reflected + m_fuzz * runit_sphere());
  attenuation = m_albedo;
  return glm::dot(scattered.direction(), rec.normal) > 0;
}
