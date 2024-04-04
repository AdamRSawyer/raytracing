#ifndef VEC3_H
#define VEC3_H

#include <string.h>
#include <cmath>
#include <iostream>
#include "Utility.h"

class Vec3
{
    public:

        double v[3]; // Contains the coordinates of the vector

        Vec3(){ this->v[0] = 0; this->v[1] = 0; this->v[2] = 0;}

        Vec3(double v_0, double v_1, double v_2)
        {
            v[0] = v_0; v[1] = v_1; v[2] = v_2;
        }

        Vec3(const Vec3 &v_init)
        {
            v[0] = v_init.v[0]; v[1] = v_init.v[1]; v[2] = v_init.v[2];
        }

        Vec3(double v[3])
        {
            memcpy(this->v, v, sizeof(double) * 3);
        }

        ~Vec3(){};

        Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }        
        double operator[](u_int64_t num) const { return v[num]; }
        double& operator[](u_int64_t num) { return v[num]; } 

        static Vec3 random() { return Vec3(random_double(), random_double(), random_double()); }
        static Vec3 random(double min, double max) { return Vec3(random_double(min, max), random_double(min, max), random_double(min, max)); }

        Vec3& operator+=(const Vec3 &add_v)
        {
            this->v[0] += add_v[0];
            this->v[1] += add_v[1];
            this->v[2] += add_v[2];
            return *this;
        }

        Vec3& operator*=(const double d)
        {
            this->v[0] *= d;
            this->v[1] *= d;
            this->v[2] *= d;
            return *this;
        }

        Vec3& operator/=(const double d)
        {
            this->v[0] /= d;
            this->v[1] /= d;
            this->v[2] /= d;
            return *this;
        }

        double magnitude() const 
        {
            return sqrt(magnitude_sqrd());
        }

        double magnitude_sqrd() const 
        {
            return pow(this->v[0], 2) + pow(this->v[1], 2) + pow(this->v[2], 2);
        }

        bool near_zero() const { return (this->magnitude_sqrd() < __DBL_EPSILON__); } // May need to make this larger value

};

inline std::ostream& operator<<(std::ostream &out, const Vec3 &vec)
{
    return out << vec[0] << ' ' << vec[1] << ' ' << vec[2];
}

inline Vec3 operator+(const Vec3 &vec1, const Vec3 &vec2)
{
    return Vec3(vec1[0] + vec2[0], vec1[1] + vec2[1], vec1[2] + vec2[2]);
}

inline Vec3 operator-(const Vec3 &vec1, const Vec3 &vec2)
{
    return Vec3(vec1[0] - vec2[0], vec1[1] - vec2[1], vec1[2] - vec2[2]);
}

inline Vec3 operator*(const Vec3 &vec1, const Vec3 &vec2)
{
    return Vec3(vec1[0] * vec2[0], vec1[1] * vec2[1], vec1[2] * vec2[2]);
}

inline Vec3 operator*(const double d, const Vec3 &vec)
{
    return Vec3(d*vec[0], d*vec[1], d*vec[2]);
}

inline Vec3 operator*(const Vec3 &vec, const double d)
{
    return d*vec;
}

inline Vec3 operator/(const Vec3 &vec, const double d)
{
    return Vec3(vec[0]/d, vec[1]/d, vec[2]/d);
}

inline double dot(const Vec3 &vec1, const Vec3 &vec2)
{
    Vec3 vecTemp = vec1 * vec2;
    return vecTemp[0] + vecTemp[1] + vecTemp[2];
}

inline Vec3 cross(const Vec3 &vec1, const Vec3 &vec2)
{
    double i = vec1[1]*vec2[2] - vec1[2]*vec2[1];
    double j = -(vec1[0]*vec2[2] - vec1[2]*vec2[0]);
    double k = vec1[0]*vec2[1] - vec1[1]*vec2[0];
    return Vec3(i, j, k);
}

inline Vec3 unit_vector(const Vec3 &vec)
{
    return Vec3(vec.v[0], vec.v[1], vec.v[2]) / vec.magnitude();
}

inline Vec3 randomInUnitSphere()
{
    return unit_vector(Vec3::random(-1.0, 1.0));
}

inline Vec3 randomOnHemisphere(const Vec3 &normal)
{
    Vec3 unitSphereVec = randomInUnitSphere();
    if (dot(unitSphereVec, normal) > 0.0) 
        return unitSphereVec;
    else
        return -unitSphereVec;
}

inline Vec3 randomUnitVector() 
{
    return randomInUnitSphere();
}

// Reflects the light ray v in the way a metal mirror would. n is the surface normal at the point of ray v's contact
inline Vec3 reflect(const Vec3 &v, const Vec3 &n)
{
    return v - 2 * dot(v, n) * n;
}

inline Vec3 refract(const Vec3 &v, const Vec3 &n, const double etaOverEtaPrime)
{
    double cosTheta = fmin(dot(-v,n), 1.0);
    Vec3 vPrimePerp = etaOverEtaPrime * (v + (cosTheta * n));
    Vec3 vPrimeParellel = -sqrt(fabs(1.0 - vPrimePerp.magnitude_sqrd())) * n;
    return vPrimePerp + vPrimeParellel; 
}

// Rotate according to the angles, rotations occur in the order z, y, x or roll, yaw, pitch
inline Vec3 rotate(const Vec3 &v, const Vec3 &angls)
{
    /*
        Rot Mat Z

        [ cos(thta) -sin(thta) 0 ]
        [ sin(thta) cos(thta)  0 ]
        [ 0         0          0 ]
    */
   Vec3 v_tmp(v);
   v_tmp.v[0] = dot(v_tmp, Vec3(cos(deg_to_rad(angls[2])), -sin(deg_to_rad(angls[2])), 0));
   v_tmp.v[1] = dot(v_tmp, Vec3(sin(deg_to_rad(angls[2])), cos(deg_to_rad(angls[2])), 0));
   v_tmp.v[2] = dot(v_tmp, Vec3(0, 0, 1));

   /*
        Rot Mat Y

        [ cos(thta)  0          sin(thta) ]
        [ 0          1          0         ]
        [ -sin(thta) 0          cos(thta) ]
    */
   v_tmp.v[0] = dot(v_tmp, Vec3(cos(deg_to_rad(angls[1])), 0, sin(deg_to_rad(angls[1]))));
   v_tmp.v[1] = dot(v_tmp, Vec3(0, 1, 0));
   v_tmp.v[2] = dot(v_tmp, Vec3(-sin(deg_to_rad(angls[1])), 0, cos(deg_to_rad(angls[1]))));

   /*
        Rot Mat X

        [ 1          0          0          ]
        [ 0          cos(thta)  -sin(thta) ]
        [ 0          sin(thta)  cos(thta)  ]
    */
   v_tmp.v[0] = dot(v_tmp, Vec3(1, 0, 0));
   v_tmp.v[1] = dot(v_tmp, Vec3(0, cos(deg_to_rad(angls[0])), -sin(deg_to_rad(angls[0]))));
   v_tmp.v[2] = dot(v_tmp, Vec3(0, sin(deg_to_rad(angls[0])), cos(deg_to_rad(angls[0]))));

   return v_tmp;

}

#endif