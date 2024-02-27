#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"

class Color : public Vec3
{
    public:
        Color(double r, double g, double b);
        Color(double c[3]);
        ~Color();

    Color& operator+=(const Color &add_p)
    {
        this->v[0] += add_p[0];
        this->v[1] += add_p[1];
        this->v[2] += add_p[2];
        return *this;
    }

    Color operator-() const { return Color(-v[0], -v[1], -v[2]); }        

    Color& operator*=(const double d)
    {
        this->v[0] *= d;
        this->v[1] *= d;
        this->v[2] *= d;
        return *this;
    }

    Color& operator/=(const double d)
    {
        this->v[0] /= d;
        this->v[1] /= d;
        this->v[2] /= d;
        return *this;
    }
};

Color::Color(double r, double g, double b)
{
    this->v[0] = r;
    this->v[1] = g;
    this->v[2] = b;
}

/*
c: colors should be in the order r, g, b and be between the 
   values 0.0 and 1.0 inclusive.
*/
Color::Color(double c[3])
{
    memcpy(this->v, c, sizeof(double) * 3);
}
Color::~Color()
{
}

inline std::ostream& operator<<(std::ostream &out, const Color &vec)
{
    out << vec[0] << ' ' << vec[1] << ' ' << vec[2];
}

inline Color operator+(const Color &vec1, const Color &vec2)
{
    return Color(vec1[0] + vec2[0], vec1[1] + vec2[1], vec1[2] + vec2[2]);
}

inline Color operator-(const Color &vec1, const Color &vec2)
{
    return Color(vec1[0] - vec2[0], vec1[1] - vec2[1], vec1[2] - vec2[2]);
}

inline Color operator*(const Color &vec1, const Color &vec2)
{
    return Color(vec1[0] * vec2[0], vec1[1] * vec2[1], vec1[2] * vec2[2]);
}

inline Color operator*(const double d, const Color &vec)
{
    return Color(d*vec[0], d*vec[1], d*vec[2]);
}

inline Color operator*(const Color &vec, const double d)
{
    return d*vec;
}

inline Color operator/(const Color &vec, const double d)
{
    return Color(vec[0]/d, vec[1]/d, vec[2]/d);
}

inline double dot(const Color &vec1, const Color &vec2)
{
    Color vecTemp = vec1 * vec2;
    return vecTemp[0] + vecTemp[1] + vecTemp[2];
}

inline Color cross(const Color &vec1, const Color &vec2)
{
    double i = vec1[1]*vec2[2] - vec1[2]*vec2[1];
    double j = -(vec1[0]*vec2[2] - vec1[2]*vec2[0]);
    double k = vec1[0]*vec2[1] - vec1[1]*vec2[0];
    return Color(i, j, k);
}

inline Color unit_vector(const Color &vec)
{
    return Color(vec.v[0], vec.v[1], vec.v[2]) / vec.magnitude();
}

#endif