#ifndef HIT_OBJECT_H
#define HIT_OBJECT_H

#include <iostream>

class HitRecord;
class Ray;

class HitObject
{
public:
  virtual bool hit(const Ray& r, std::pair<float, float> t_lim,
                   HitRecord& rec) const = 0;
};

#endif // HIT_OBJECT_H
