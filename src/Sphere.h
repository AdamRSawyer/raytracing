#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "Hittable.h"
#include "Vec3.h"


class Sphere : public Hittable 
{
    public:
        Sphere(Vec3 center, double radius, std::shared_ptr<Material> mat) : center(center), radius(radius), mat(mat) {}

        bool hit(const Ray& r, const Interval& ray_t, Hit_Record& rec) const override;
    private:
        Vec3 center;
        double radius;
        std::shared_ptr<Material> mat;


};

bool Sphere::hit(const Ray&r, const Interval& ray_t, Hit_Record& rec) const
{
    double quad_a = r.direction().magnitude_sqrd();
    double quad_b = dot(r.direction(), r.origin() - center); 
    double quad_c = (r.origin() - center).magnitude_sqrd() - (radius * radius);

    double determinant = (quad_b * quad_b) - (quad_a * quad_c);

    if (determinant < 0.0)
        return false;
    else if(determinant > 0.0)
    {
        double det_sqrt = sqrt(determinant);

        double sol_1 = (- quad_b - det_sqrt) / quad_a;
        double sol_2 = (- quad_b + det_sqrt) / quad_a;

        if (sol_1 <= sol_2 && ray_t.contains(sol_1))
        {
            rec.t = sol_1;
            rec.p = r.at(sol_1);
            rec.set_face_normal(r, (rec.p - center) / radius);
            rec.mat = mat;
            
            return true;
        }
        else if (ray_t.contains(sol_2))
        {
            rec.t = sol_2;
            rec.p = r.at(sol_2);
            rec.set_face_normal(r, (rec.p - center) / radius);
            rec.mat = mat;

            return true;
        }

        return false;
    }
    else
    {
        double det_sqrt = sqrt(determinant);
        double sol = (- quad_b - det_sqrt) / quad_a;

        if (ray_t.contains(sol))
        {
            rec.t = sol;
            rec.p = r.at(sol);
            rec.set_face_normal(r, (rec.p - center) / radius);
            rec.mat = mat;

            return true;
        }

        return false;
    }

}

#endif