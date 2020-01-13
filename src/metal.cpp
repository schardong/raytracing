#include "material.h"
#include "hitrecord.h"
#include "ray.h"
#include "utils.h"

Metal::Metal(glm::vec3 albedo, float fuzz) : m_albedo(albedo)
{
  m_fuzz = std::min(1.f, std::max(fuzz, 0.f));
}

bool Metal::scatter(const Ray& r_in, const HitRecord& rec,
                    glm::vec3& attenuation, Ray& scattered) const
{
  glm::vec3 reflected = reflect(glm::normalize(r_in.direction()), rec.normal);
  scattered = Ray(rec.p, reflected + m_fuzz * runit_sphere());
  attenuation = m_albedo;
  return glm::dot(scattered.direction(), rec.normal) > 0;
}
