#include "hitobjectlist.h"
#include "ray.h"
#include "hitrecord.h"

HitObjectList::HitObjectList() {}

HitObjectList::~HitObjectList()
{
  for (size_t i = 0; i < m_objects.size(); ++i)
    delete m_objects[i];
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

void HitObjectList::pushObject(HitObject* obj)
{
  m_objects.push_back(obj);
}
