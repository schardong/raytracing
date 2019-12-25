#ifndef MATERIAL_H
#define MATERIAL_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class HitRecord;
class Ray;

class Material
{
public:
  virtual ~Material() {};
  virtual bool scatter(const Ray& r_in, const HitRecord& rec,
                       glm::vec3& attenuation, Ray& scattered) const = 0;
};

class Lambertian: public Material
{
public:
  Lambertian(glm::vec3 albedo);
  virtual ~Lambertian() = default;
  virtual bool scatter(const Ray& r_in, const HitRecord& rec,
                       glm::vec3& attenuation, Ray& scattered) const;

private:
  glm::vec3 m_albedo;
};

class Metal: public Material
{
public:
  Metal(glm::vec3 albedo, float fuzz = 0.f);
  virtual ~Metal() = default;
  virtual bool scatter(const Ray& r_in, const HitRecord& rec,
                       glm::vec3& attenuation, Ray& scattered) const;
private:
  glm::vec3 m_albedo;
  float m_fuzz;
};

class Dielectric: public Material
{
public:
  Dielectric(float ri);
  virtual ~Dielectric() = default;
  virtual bool scatter(const Ray& r_in, const HitRecord& rec,
                       glm::vec3& attenuation, Ray& scattered) const;

private:
  float m_refraction_index;
};

#endif // MATERIAL_H
