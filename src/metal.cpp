#include "material.h"
#include "hitrecord.h"
#include "ray.h"
#include "utils.hpp"

Metal::Metal(glm::vec3 albedo) : m_albedo(albedo) {}

bool Metal::scatter(const Ray& r_in, const HitRecord& rec,
                    glm::vec3& attenuation, Ray& scattered) const
{
  glm::vec3 reflected = reflect(glm::normalize(r_in.direction()), rec.normal);
  scattered = Ray(rec.p, reflected);
  attenuation = m_albedo;
  return glm::dot(scattered.direction(), rec.normal) > 0;
}
