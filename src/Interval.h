#ifndef INTERVAL_H
#define INTERVAL_H

#include "Utility.h"


class Interval
{
    public:
        double min, max;

        Interval() : min(INF), max(-INF) {}
        Interval(double min, double max) : min(min), max(max) {}

        bool contains(double x) const { return (x >= min && x <= max); }
        bool surrounds(double x) const { return (x > min && x < max); }

        double clamp(double x) const
        {
            if (x < min){ return min; }
            if (x > max){ return max; }
            return x;
        }

    static const Interval empty, universe, clrIntrv;

};

const static Interval empty();
const static Interval universe(-INF, INF);
const static Interval clrIntrv(0.000, 0.999);

#endif