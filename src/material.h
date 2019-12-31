#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class HitRecord;
class Ray;
class Texture;

class Material
{
public:
  virtual ~Material() {};
  virtual bool scatter(const Ray& r_in, const HitRecord& rec,
                       glm::vec3& attenuation, Ray& scattered) const = 0;
  virtual glm::vec3 emit() const
  {
    return glm::vec3(0.f);
  }
};

class Lambertian: public Material
{
public:
  Lambertian(std::unique_ptr<Texture> albedo);
  virtual ~Lambertian() = default;
  virtual bool scatter(const Ray& r_in, const HitRecord& rec,
                       glm::vec3& attenuation, Ray& scattered) const;

private:
  std::unique_ptr<Texture> m_albedo;
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

class DiffuseLight : public Material
{
public:
  DiffuseLight(glm::vec3 color);
  ~DiffuseLight() = default;
  virtual bool scatter(const Ray& r_in, const HitRecord& rec,
                       glm::vec3& attenuation, Ray& scattered) const;
  virtual glm::vec3 emit() const;

private:
  glm::vec3 m_color;
};

#endif // MATERIAL_H
