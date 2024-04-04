#ifndef METAL_H
#define METAL_H

#include "Material.h"

class Metal : public Material
{
    public:
        Metal(Color albedo, double fuzz = 0) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {};

        bool scatter(const Ray& r_in, const Hit_Record& rec, Color& attenuation, Ray& scattered) const override 
        {
            attenuation = albedo;
            scattered = Ray(rec.p, reflect(r_in.direction(), rec.normal) + randomUnitVector() * fuzz);
            return (dot(scattered.direction(), rec.normal) > 0);

        }

    private:
        Color albedo;
        double fuzz;

};

#endif