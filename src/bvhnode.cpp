#include "bvhnode.h"
#include "aabb.h"
#include "hitrecord.h"
#include "ray.h"
#include "utils.hpp"

#include <algorithm>
#include <cmath>

bool box_x_compare(HitObject* a, HitObject* b)
{
  AABB box_a, box_b;
  if (!a->bounding_box(box_a) || !b->bounding_box(box_b)) {
    throw std::logic_error("One object has no bounding box.");
  }
  return box_a.bottom()[0] < box_b.bottom()[0];
}

bool box_y_compare(HitObject* a, HitObject* b)
{
  AABB box_a, box_b;
  if (!a->bounding_box(box_a) || !b->bounding_box(box_b)) {
    throw std::logic_error("One object has no bounding box.");
  }
  return box_a.bottom()[1] < box_b.bottom()[1];
}

bool box_z_compare(HitObject* a, HitObject* b)
{
  AABB box_a, box_b;
  if (!a->bounding_box(box_a) || !b->bounding_box(box_b)) {
    throw std::logic_error("One object has no bounding box.");
  }
  return box_a.bottom()[2] < box_b.bottom()[2];
}

BVHNode::BVHNode(std::vector<HitObject*> objs)
{
  if (objs.empty())
    throw std::logic_error("No objects to include in BVH.");

  if (objs.size() == 1) {
    left = right = objs[0];
  } else {
    int ax = static_cast<int>(floor(3 * rdouble()));
    bool (*comps[])(HitObject*, HitObject*) = {box_x_compare, box_y_compare, box_z_compare};
    std::sort(objs.begin(), objs.end(), comps[ax]);

    size_t sz = objs.size();
    if (sz == 2) {
      left = objs[0];
      right = objs[1];
    } else {
      left = new BVHNode(std::vector<HitObject*>(objs.begin(), objs.begin() + floor(sz/2)));
      right = new BVHNode(std::vector<HitObject*>(objs.begin() + ceil(sz/2), objs.end()));
    }
  }

  AABB box_left, box_right;
  if (!left->bounding_box(box_left) || !right->bounding_box(box_right))
    throw std::logic_error("BVH children have no valid AABB.");

  m_box = AABB(box_left, box_right);
}

BVHNode::~BVHNode()
{
  if (left) {
    delete left;
    left = nullptr;
  }
  if (right) {
    delete right;
    right = nullptr;
  }
}

bool BVHNode::hit(const Ray& r, std::pair<float, float> t_lim, HitRecord& rec) const
{
  if (m_box.hit(r, t_lim)) {
    HitRecord rec_left, rec_right;
    bool hit_left = false;
    bool hit_right = false;
    hit_left = left->hit(r, t_lim, rec_left);
    hit_right = right->hit(r, t_lim, rec_right);

    if (hit_left && hit_right) {
      rec = rec_left.t < rec_right.t? rec_left : rec_right;
      return true;
    } else if (hit_left) {
      rec = rec_left;
      return true;
    } else if (hit_right) {
      rec = rec_right;
      return true;
    } else {
      return false;
    }
  }
  return false;
}

bool BVHNode::bounding_box(AABB& box) const
{
  box = m_box;
  return true;
}
