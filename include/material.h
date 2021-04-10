#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class HitRecord;
class Ray;
class Texture;


/**
 * @brief Base class for all materials.
 *
 * All subclasses must implement the `scatter` method. All materials that emit
 * light must also override the `emit` method, which by default, returns
 * `vec3(0)`.
 */
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


/**
 * @brief Class for general diffuse materials.
 *
 * This class represents diffuse, non-emitting materials. They don't have a
 * specularity component on their color. This class also supports textures.
 *
 * @seealso Texture
 */
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


/**
 * @brief Class for metallic materials.
 *
 * This class represents metallic materials. While they reflect light, they
 * don't emit any. Such materials have an innate color, but no texture. They
 * may also be fuzzy, i.e. the reflecting rays are slightly perturbed, thus
 * giving a diffuse aspect to the material.
 */
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


/**
 * @brief Class for dielectric materials, i.e. glass.
 *
 * This class represents materials that refract light, such as glass. This
 * material has no color, being fully transparent. The only parameter is the
 * refraction index of the material
 */
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


/**
 * @brief Class for light emitting materials
 *
 * This material does not reflect or refract light in any way, only emits it.
 * The light color is passed as a parameter to the constructor.
 */
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
