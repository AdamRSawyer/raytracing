#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable 
{
    public:
        Sphere(Vec3 center, double radius) : center(center), radius(radius) {}

        bool hit(const Ray& r, double ray_tmin, double ray_tmax, Hit_Record& rec) const override;
    private:
        Vec3 center;
        double radius;


};

bool Sphere::hit(const Ray&r, double ray_tmin, double ray_tmax, Hit_Record& rec) const
{
    double quad_a = r.direction().magnitude_sqrd();
    double quad_b = dot(r.direction(), r.origin() - center); 
    double quad_c = (r.origin() - center).magnitude_sqrd() - (radius * radius);

    double determinant = (quad_b * quad_b) - (quad_a * quad_c);

    if (determinant < -__DBL_EPSILON__)
        return false;
    else if(determinant > __DBL_EPSILON__)
    {
        double det_sqrt = sqrtl(determinant);

        double sol_1 = (- quad_b + det_sqrt) / quad_a;
        double sol_2 = (- quad_b - det_sqrt) / quad_a;

        if (sol_1 <= sol_2 && sol_1 >= ray_tmin && sol_1 <= ray_tmax)
        {
            rec.t = sol_1;
            rec.p = r.at(sol_1);
            rec.set_face_normal(r, unit_vector(rec.p - center));
            
            return true;
        }
        else if (sol_2 >= ray_tmin && sol_2 <= ray_tmax)
        {
            rec.t = sol_2;
            rec.p = r.at(sol_2);
            rec.set_face_normal(r, unit_vector(rec.p - center));

            return true;
        }

        return false;
    }
    else
    {
        double det_sqrt = sqrtl(determinant);
        double sol = (- quad_b + det_sqrt) / quad_a;

        if (sol >= ray_tmin && sol <= ray_tmax)
        {
            rec.t = sol;
            rec.p = r.at(sol);
            rec.set_face_normal(r, unit_vector(rec.p - center));

            return true;
        }

        return false;
    }

}

#endif