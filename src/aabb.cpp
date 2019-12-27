#include "aabb.h"
#include "ray.h"

using glm::vec3;

AABB::AABB(vec3 x1, vec3 x2) : m_min(x1), m_max(x2) {}

AABB::AABB(AABB box0, AABB box1)
{
  m_min = vec3(std::min(box0.bottom().x, box1.bottom().x),
               std::min(box0.bottom().y, box1.bottom().y),
               std::min(box0.bottom().z, box1.bottom().z));

  m_max = vec3(std::max(box0.top().x, box1.top().x),
               std::max(box0.top().y, box1.top().y),
               std::max(box0.top().z, box1.top().z));
}

vec3 AABB::bottom() const { return m_min; }

vec3 AABB::top() const { return m_max; }

bool AABB::hit(const Ray& r_in, std::pair<float, float> t_lim) const
{
  float tmin = t_lim.first;
  float tmax = t_lim.second;
  vec3 invD = 1.0f / r_in.direction();

  for (int i = 0; i < 3; ++i) {
    float t0 = (bottom()[i] - r_in.origin()[i]) * invD[i];
    float t1 = (top()[i] - r_in.origin()[i]) * invD[i];

    if (invD[i] < 0.f)
      std::swap(t0, t1);

    tmin = t0 > tmin? t0 : tmin;
    tmax = t1 < tmax? t1 : tmax;
    if (tmax <= tmin)
      return false;
  }
  return true;
}
