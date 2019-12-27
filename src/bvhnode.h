#ifndef BVH_NODE_H
#define BVH_NODE_H

#include <vector>
#include "hitobject.h"
#include "aabb.h"

class AABB;
class HitRecord;
class Ray;

class BVHNode: public HitObject
{
public:
  BVHNode() = default;
  BVHNode(std::vector<HitObject*> objs);
  virtual ~BVHNode();

  virtual bool hit(const Ray& r, std::pair<float, float> t_lim,
                   HitRecord& rec) const;
  virtual bool bounding_box(AABB& box) const;

private:
  HitObject* left;
  HitObject* right;

  AABB m_box;
};

#endif // BVH_NODE_H
