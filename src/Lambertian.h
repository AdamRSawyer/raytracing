#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"

class Lambertian : public Material
{

    public:
        Lambertian(const Color& albedo) : albedo(albedo) {};

        bool scatter(const Ray& r_in, const Hit_Record& rec, Color& attenuation, Ray& scattered) const override 
        {

            Vec3 scatterDir = rec.normal + randomUnitVector();
            if (scatterDir.near_zero())
                scatterDir = rec.normal;

            scattered = Ray(rec.p, scatterDir);
            attenuation = albedo;
            return true;
        }

    private:
        Color albedo;

};

#endif