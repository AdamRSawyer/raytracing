#ifndef POINT3_H
#define POINT3_H

#include "Vec3.h"

class Point3 : public Vec3
{

    public:
        Point3();
        Point3(double x, double y, double z);
        Point3(double p[3]);
        Point3(const Vec3 &vec)
        {
            this->v[0] = vec[0];
            this->v[1] = vec[1];
            this->v[2] = vec[2];
        };

        ~Point3();

    Point3& operator+=(const Point3 &add_p)
    {
        this->v[0] += add_p[0];
        this->v[1] += add_p[1];
        this->v[2] += add_p[2];
        return *this;
    }

    Point3 operator-() const { return Point3(-v[0], -v[1], -v[2]); }        

    Point3& operator*=(const double d)
    {
        this->v[0] *= d;
        this->v[1] *= d;
        this->v[2] *= d;
        return *this;
    }

    Point3& operator/=(const double d)
    {
        this->v[0] /= d;
        this->v[1] /= d;
        this->v[2] /= d;
        return *this;
    }

};

Point3::Point3()
{
    this->v[0] = 0; this->v[1] = 0; this->v[2] = 0;
}

Point3::Point3(double x, double y, double z)
{
    this->v[0] = x;
    this->v[1] = y;
    this->v[2] = z;
}

/*
p: points should be in the order x, y, z
*/
Point3::Point3(double p[3])
{
    memcpy(this->v, p, sizeof(double) * 3);
}

Point3::~Point3()
{
}

inline std::ostream& operator<<(std::ostream &out, const Point3 &vec)
{
    return out << vec[0] << ' ' << vec[1] << ' ' << vec[2];
}

inline Point3 operator+(const Point3 &vec1, const Point3 &vec2)
{
    return Point3(vec1[0] + vec2[0], vec1[1] + vec2[1], vec1[2] + vec2[2]);
}

inline Point3 operator-(const Point3 &vec1, const Point3 &vec2)
{
    return Point3(vec1[0] - vec2[0], vec1[1] - vec2[1], vec1[2] - vec2[2]);
}

inline Point3 operator*(const Point3 &vec1, const Point3 &vec2)
{
    return Point3(vec1[0] * vec2[0], vec1[1] * vec2[1], vec1[2] * vec2[2]);
}

inline Point3 operator*(const Vec3 &vec1, const Point3 &vec2)
{
    return Point3(vec1[0] * vec2[0], vec1[1] * vec2[1], vec1[2] * vec2[2]);
}

inline Point3 operator*(const double d, const Point3 &vec)
{
    return Point3(d*vec[0], d*vec[1], d*vec[2]);
}

inline Point3 operator*(const Point3 &vec, const double d)
{
    return d*vec;
}

inline Point3 operator/(const Point3 &vec, const double d)
{
    return Point3(vec[0]/d, vec[1]/d, vec[2]/d);
}

inline double dot(const Point3 &vec1, const Point3 &vec2)
{
    Point3 vecTemp = vec1 * vec2;
    return vecTemp[0] + vecTemp[1] + vecTemp[2];
}

inline double dot(const Vec3 &vec1, const Point3 &vec2)
{
    Point3 vecTemp = vec1 * vec2;
    return vecTemp[0] + vecTemp[1] + vecTemp[2];
}

inline Point3 cross(const Point3 &vec1, const Point3 &vec2)
{
    double i = vec1[1]*vec2[2] - vec1[2]*vec2[1];
    double j = -(vec1[0]*vec2[2] - vec1[2]*vec2[0]);
    double k = vec1[0]*vec2[1] - vec1[1]*vec2[0];
    return Point3(i, j, k);
}

inline Point3 unit_vector(const Point3 &vec)
{
    return Point3(vec.v[0], vec.v[1], vec.v[2]) / vec.magnitude();
}

inline Point3 operator+(const Vec3 &vec1, const Point3 &vec2)
{
    return Point3(vec1[0] + vec2[0], vec1[1] + vec2[1], vec1[2] + vec2[2]);
}

inline Point3 operator-(const Vec3 &vec1, const Point3 &vec2)
{
    return Point3(vec1[0] - vec2[0], vec1[1] - vec2[1], vec1[2] - vec2[2]);
}

inline Point3 operator+(const Point3 &vec1, const Vec3 &vec2)
{
    return vec2 + vec1;
}

inline Point3 operator-(const Point3 &vec1, const Vec3 &vec2)
{
    return Point3(vec1[0] - vec2[0], vec1[1] - vec2[1], vec1[2] - vec2[2]);
}

#endif