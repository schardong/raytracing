#ifndef TRACE_H
#define TRACE_H

#include "utils.h"

class HitObject;
class Ray;
class Camera;

glm::vec3 color(const Ray& r, const HitObject& world, int depth);

void trace(HitObject* world, Camera& cam, ImgData& img_data,
           int samples_per_pix);

#endif // TRACE_H
