#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.h"

class Dielectric : public Material
{
    public:
        Dielectric(double refractionIdx) : refractionIdx(refractionIdx) {}

        bool scatter(const Ray& r_in, const Hit_Record& rec, Color& attenuation, Ray& scattered) const override
        {
            double refRatio = rec.front_face ? (1.0 / refractionIdx) : refractionIdx;
            Vec3 r_in_unitVec = unit_vector(r_in.direction());
            double cosTheta = fmin(dot(-r_in_unitVec, rec.normal), 1.0);
            double sinTheta =  sqrt(1.0 - pow(cosTheta, 2));

            if ((refRatio * sinTheta) > 1.0 || reflectance(cosTheta, refRatio) > random_double()) // No solution to snells law and refleciton occurs
            {
                scattered = Ray(rec.p, reflect(r_in_unitVec, rec.normal));
            }
            else
            {
                scattered = Ray(rec.p, refract(r_in_unitVec, rec.normal, refRatio));
            }
            attenuation = Color(1.0, 1.0, 1.0);
            return true;
        }

    private:
        double refractionIdx;

        // Schlick reflectance approximation
        static double reflectance(double cos, double refIdx)
        {
            double r0 = pow((1.0 - refIdx) / (1.0 + refIdx), 2);
            return r0 + (1.0 - r0) * pow((1.0 - cos), 5);
        }
};

#endif