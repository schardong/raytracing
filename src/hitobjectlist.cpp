#include "hitobjectlist.h"
#include "aabb.h"
#include "ray.h"
#include "hitrecord.h"

HitObjectList::HitObjectList(std::vector<HitObject*>& objs) :
  m_objects(objs)
{}

HitObjectList::~HitObjectList()
{
  for (auto it : m_objects) {
    delete it;
    it = nullptr;
  }
  m_objects.clear();
}

bool HitObjectList::hit(const Ray& r, std::pair<float, float> t_lims,
                        HitRecord& rec) const
{
  HitRecord tmp;
  bool hit_any = false;
  float closest = t_lims.second;

  for (const auto& obj : m_objects) {
    if (obj->hit(r, std::make_pair(t_lims.first, closest), tmp)) {
      hit_any = true;
      closest = tmp.t;
      rec = tmp;
    }
  }

  return hit_any;
}

bool HitObjectList::bounding_box(AABB& box) const
{
  if (m_objects.empty())
    return false;

  AABB tmp;

  if (m_objects[0]->bounding_box(tmp))
    box = tmp;
  else
    return false;

  for (size_t i = 1; i < m_objects.size(); ++i) {
    if (m_objects[i]->bounding_box(tmp))
      box = AABB(box, tmp);
    else
      return false;
  }

  return true;
}

void HitObjectList::pushObject(HitObject* obj)
{
  m_objects.push_back(obj);
}
