#ifndef TRACE_H
#define TRACE_H

#include "utils.h"

class HitObject;
class Ray;
class Camera;

/**
 * @brief Base ray tracer class
 */
class Tracer
{
public:
  virtual glm::vec3 color(const Ray& r, const HitObject& world,
                          int depth) const = 0;
  virtual void trace(HitObject* world, Camera& cam, ImgData& img_data,
                     int samples_per_pix) const;
};

/**
 * @brief A debugging tracer to show the normals of all objects in the scene.
 */
class NormalTracer : public Tracer
{
public:
  virtual glm::vec3 color(const Ray& r, const HitObject& world,
                          int depth) const;
};

/**
 * @brief
 */
class LightTracer : public Tracer
{
public:
  virtual glm::vec3 color(const Ray& r, const HitObject& world,
                          int depth) const;
};

#endif // TRACE_H
