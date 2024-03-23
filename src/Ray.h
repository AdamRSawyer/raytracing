#ifndef RAY_H
#define RAY_H

#include "Point3.h"
#include "Color.h"

class Ray
{
    public:

        Ray(const Point3& origin, const Vec3& dir){ this->orig = origin; this->dir = unit_vector(dir); }
        ~Ray(){};

        Point3 at(double t) const { return orig + t*dir; }

        const Point3 origin() { return orig; }
        const Vec3 direction() { return dir; }

    private:
        Point3 orig;
        Vec3 dir;

};




#endif