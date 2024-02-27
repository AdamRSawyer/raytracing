#ifndef VEC3_H
#define VEC3_H

#include <string.h>
#include <cmath>
#include <iostream>

class Vec3
{
    public:

        double v[3]; // Contains the coordinates of the vector

        Vec3(){ this->v[0] = 0; this->v[1] = 0; this->v[2] = 0;}

        Vec3(double v_0, double v_1, double v_2)
        {
            v[0] = v_0; v[1] = v_1; v[2] = v_2;
        }

        Vec3(double v[3])
        {
            memcpy(this->v, v, sizeof(double) * 3);
        }

        ~Vec3(){};

        Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }        
        double operator[](u_int64_t num) const { return v[num]; }
        double& operator[](u_int64_t num) { return v[num]; } 

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

#endif