//#define WIN_32
//#define LINUX
#define APPLE

#include <iostream>
#include "Point3.h"
#include "Color.h"
#include "raytracer_Funcs.cpp"
#include "Ray.h"

void clearTerminal();
void drawProgressBar(float percComplete);
Color rayColor(const Ray& r);

int main()
{
    const double aspectRatio = 16.0/9.0;
    uint16_t imageHeight = 256;
    uint16_t imageWidth = (static_cast<uint16_t>(imageHeight * aspectRatio) > 1) ? static_cast<uint16_t>(imageHeight * aspectRatio) : 0;

    double viewPortHeight = 2.0;
    double viewPortWidth = viewPortHeight * (double(imageWidth) / imageHeight);

    Point3 cameraCenter(0, 0, 0);
    double focalLength = 1;

    Vec3 viewPort_u(viewPortWidth, 0, 0); // Horizontal viewport vector
    Vec3 viewPort_v(0, -viewPortHeight, 0); // Vertical viewport vector

    Vec3 delta_u = viewPort_u / imageWidth;
    Vec3 delta_v = viewPort_v / imageHeight;

    Point3 Q = cameraCenter + Vec3(0, 0, focalLength) - viewPort_u / 2 - viewPort_v / 2; // Upper left viewpoint corner
    Point3 P_00 = Q + delta_u / 2 + delta_v / 2; // Top left pixel

    Color pixels[imageHeight * imageWidth];

    for (int i = 0; i < imageHeight; ++i)
    {
        clearTerminal();
        drawProgressBar(float(i) / imageHeight);

        for (int j = 0; j < imageWidth; ++j)
        {
            Point3 curPixlPos = P_00 + delta_u * j + delta_v * i;
            Ray curRay(cameraCenter, static_cast<Vec3>(curPixlPos - cameraCenter));
            
            uint64_t curRGB_Triplet = i * imageWidth + j; 
            pixels[curRGB_Triplet] = rayColor(curRay);
        }
    }

    clearTerminal();
    drawProgressBar(1);

    RT_UTILITIES::writePPM("./imageOut.ppm", imageWidth, imageHeight, pixels);


    return 0;
}

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

Color rayColor(const Ray& r)
{
    return Color(0, 0, 0);
}