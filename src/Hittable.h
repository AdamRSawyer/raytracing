#ifndef HITTABLE_H
#define HITTABLE_H

#include <memory>
#include "Interval.h"
#include "Ray.h"

class Material;

class Hit_Record 
{
    public:
        Point3 p;
        Vec3 normal;
        std::shared_ptr<Material> mat;
        double t;
        bool front_face;

        void set_face_normal(const Ray& r, const Vec3& outside_normal)
        {
            // outside_normal is assumed to be a unit vector
            if (dot(r.direction(), outside_normal) < 0.0)
            {
                // The ray is outside the sphere because they are facing the opposite direction
                normal = outside_normal;
                front_face = true;
            }
            else
            {
                normal = -outside_normal;
                front_face = false;
            }
        }
};

class Hittable
{
    public:
        virtual ~Hittable() = default;

        virtual bool hit(const Ray& r, const Interval& ray_t, Hit_Record& rec) const = 0;
};



#endif