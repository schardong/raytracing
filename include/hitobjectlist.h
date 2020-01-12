#ifndef HIT_OBJECT_LIST_H
#define HIT_OBJECT_LIST_H

#include <vector>
#include "hitobject.h"

class AABB;
class HitRecord;

class HitObjectList: public HitObject
{
public:
  HitObjectList() = default;
  HitObjectList(std::vector<HitObject*>& objs);
  virtual ~HitObjectList();

  virtual bool hit(const Ray &r, std::pair<float, float> t_lims,
                   HitRecord &rec) const;
  virtual bool bounding_box(AABB& box) const;

  void pushObject(HitObject* obj);

private:
  std::vector<HitObject*> m_objects;
};

#endif // HIT_OBJECT_LIST_H
