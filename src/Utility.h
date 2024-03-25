#ifndef UTILITY_H
#define UTILITY_H

#include <limits>

// Constants

const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// Utility Funcs

inline double deg_to_rad(double deg) { return deg * PI / 180.0; }

#endif