#include "material.h"
#include "hitrecord.h"
#include "ray.h"
#include "utils.hpp"

float schlick(float cosine, float ref_idx)
{
  float r0 = (1 - ref_idx) / (1 + ref_idx);
  r0 = r0 * r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}

Dielectric::Dielectric(float ri) : m_refraction_index(ri) {}

bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec,
                         glm::vec3& attenuation, Ray& scattered) const
{
  using glm::vec3;
  using glm::dot;

  vec3 outward_n;
  vec3 reflected = reflect(r_in.direction(), rec.normal);
  float ni_over_nt;
  attenuation = vec3(1.0f);
  vec3 refracted;

  float reflect_prob;
  float cosine;

  if (dot(r_in.direction(), rec.normal) > 0) {
    outward_n = -rec.normal;
    ni_over_nt = m_refraction_index;
    cosine = m_refraction_index * dot(r_in.direction(), rec.normal) /
      r_in.direction().length();
  } else {
    outward_n = rec.normal;
    ni_over_nt = 1.0f / m_refraction_index;
    cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
  }

  if (refract(r_in.direction(), outward_n, ni_over_nt, refracted))
    reflect_prob = schlick(cosine, m_refraction_index);
  else
    reflect_prob = 1.0f;

  if (rdouble() < reflect_prob)
    scattered = Ray(rec.p, reflected);
  else
    scattered = Ray(rec.p, refracted);

  return true;
}
