#ifndef MATERIAL_H
#define MATERIAL_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class HitRecord;
class Ray;

class Material
{
public:
  virtual bool scatter(const Ray& r_in, const HitRecord& rec,
                       glm::vec3& attenuation, Ray& scattered) const = 0;
};

class Lambertian: public Material
{
public:
  Lambertian(glm::vec3 albedo);
  virtual bool scatter(const Ray& r_in, const HitRecord& rec,
                       glm::vec3& attenuation, Ray& scattered) const;

private:
  glm::vec3 m_albedo;
};

class Metal: public Material
{
public:
  Metal(glm::vec3 albedo);
  virtual bool scatter(const Ray& r_in, const HitRecord& rec,
                       glm::vec3& attenuation, Ray& scattered) const;
private:
  glm::vec3 m_albedo;
};

#endif // MATERIAL_H
