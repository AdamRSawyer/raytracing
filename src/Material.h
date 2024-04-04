#ifndef MATERIAL_H
#define MATERIAL_H

#include "Ray.h"
#include "Hittable.h"
#include "Color.h"


class Material
{
    public:
        virtual ~Material() = default;
        virtual bool scatter(const Ray& r_in, const Hit_Record& rec, Color& attenuation, Ray& scattered) const = 0;

};

#endif