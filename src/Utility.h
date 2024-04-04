#ifndef UTILITY_H
#define UTILITY_H

#include <limits>
#include <cstdlib>

// Constants

const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// Utility Funcs

inline double deg_to_rad(double deg) { return deg * PI / 180.0; }

void clearTerminal()
{
    #if defined (APPLE) || (LINUX)
        system("clear");
    #elif defined WIN_32
        system("cls");
    #endif
}

// Draws progress bar divided into 20 segments
/*
    percComplete: value between 0.0 and 1.0 inclusive
*/
void drawProgressBar(float percComplete)
{
    char progressBar[23];
    uint16_t cmpltSegCnt = percComplete * 20;
    
    progressBar[0] = '[';
    for (int i = 1; i < 21; ++i)
    {
        if (i - 1 < cmpltSegCnt)
        {
            progressBar[i] = '=';
        }
        else
        {
            progressBar[i] = '-';
        }
    }
    progressBar[21] = ']';

    std::cout << progressBar << ' ' << percComplete * 100 << "%" << std::endl;
}

double random_double() // produces double between 0.0 <= x < 1.0
{
    return (rand() / (RAND_MAX + 1.0));
}

double random_double(double min, double max) 
{
    return (random_double() * (max - min)) + min;
}

#endif