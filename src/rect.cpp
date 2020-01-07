#include "rect.h"
#include "aabb.h"
#include "hitrecord.h"
#include "material.h"
#include "ray.h"
#include "texture.h"

Rect::Rect() : m_bl(glm::vec3(0.f)), m_tr(glm::vec3(1.f, 1.f, 0.f)),
               m_flip_normal(false)

{
  m_material = std::make_shared<Lambertian>(std::make_unique<ConstantTexture>(glm::vec3(0.f)));
}

Rect::Rect(glm::vec2 origin, std::pair<float, float> width_height,
           Material* mat, bool flip_normal) :
  m_material(mat),
  m_flip_normal(flip_normal)
{
  m_bl = glm::vec3(origin.x, origin.y, 0.f);
  m_tr = glm::vec3(origin.x + width_height.first,
                   origin.y + width_height.second,
                   0.f);
}

Rect::~Rect()
{
  m_material.reset();
}

bool Rect::hit(const Ray &r, std::pair<float, float> t_lims, HitRecord &rec) const
{
  float t = -r.origin().z / r.direction().z;
  if (t < t_lims.first || t > t_lims.second)
    return false;

  float x = r.origin().x + t * r.direction().x;
  float y = r.origin().y + t * r.direction().y;
  if (x < m_bl.x || x > m_tr.x || y < m_bl.y || y > m_tr.y)
    return false;

  //rec.u = (x - m_bl.x) / (m_tr.x - m_bl.x);
  //rec.v = (y - m_bl.y) / (m_tr.y - m_bl.y);
  rec.t = t;
  rec.material = m_material;
  rec.p = r.p(t);

  if (m_flip_normal)
    rec.normal = glm::vec3(0, 0, -1);
  else
    rec.normal = glm::vec3(0, 0, 1);

  return true;
}

bool Rect::bounding_box(AABB &box) const
{
  box = AABB(glm::vec3(m_bl.x, m_bl.y, -0.0001f),
             glm::vec3(m_tr.x, m_tr.y, 0.0001f));
  return true;
}
