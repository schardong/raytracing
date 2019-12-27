#include "sphere.h"
#include "aabb.h"
#include "material.h"
#include "hitrecord.h"
#include "ray.h"

using glm::dot;
using glm::vec3;

Sphere::Sphere() : m_center(vec3(0)), m_radius(1.f),
                   m_material(new Lambertian(vec3(0.f))) {}

Sphere::Sphere(vec3 center, float r, Material* mat) :
  m_center(center), m_radius(r), m_material(mat) {}

bool Sphere::hit(const Ray& r, std::pair<float, float> t_lim, HitRecord& rec) const
{
  vec3 oc = r.origin() - m_center;
  float a = dot(r.direction(), r.direction());
  float b = 2.f * dot(oc, r.direction());
  float c = dot(oc, oc) - m_radius * m_radius;
  float discriminant = b * b - 4.f * a * c;

  if (discriminant > 0.f) {
    float x1 = (-b - sqrt(discriminant)) / (2.f * a);
    if (x1 < t_lim.second && x1 > t_lim.first) {
      rec.t = x1;
      rec.p = r.p(x1);
      rec.normal = (rec.p - m_center) / m_radius;
      rec.material = m_material;
      return true;
    }

    float x2 = (-b + sqrt(discriminant)) / (2.f * a);
    if (x2 < t_lim.second && x2 > t_lim.first) {
      rec.t = x2;
      rec.p = r.p(x2);
      rec.normal = (rec.p - m_center) / m_radius;
      rec.material = m_material;
      return true;
    }
  }

  return false;
}

bool Sphere::bounding_box(AABB& box) const
{
  box = AABB(center() - vec3(radius()),
             center() + vec3(radius()));
  return true;
}

const vec3 Sphere::center() const { return m_center; }

const float Sphere::radius() const { return m_radius; }
