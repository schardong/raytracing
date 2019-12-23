#ifndef HIT_OBJECT_LIST_H
#define HIT_OBJECT_LIST_H

#include <vector>
#include "hitobject.h"

class HitRecord;

class HitObjectList: public HitObject
{
public:
  HitObjectList();
  ~HitObjectList();
  virtual bool hit(const Ray &r, std::pair<float, float> t_lims,
                   HitRecord &rec) const;
  void pushObject(HitObject *obj);

private:
  std::vector<HitObject *> m_objects;
};

#endif // HIT_OBJECT_LIST_H
