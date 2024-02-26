#include <iostream>
#include "raytracer_Funcs.cpp"

int main()
{
    uint16_t imageWidth = 256;
    uint16_t imageHeight = 256;

    double pixels[imageHeight * imageWidth * 3];

    for (int i = 0; i < imageHeight; ++i)
    {
        for (int j = 0; j < imageWidth; ++j)
        {
            uint64_t curRGB_Triplet = i * imageWidth * 3 + j * 3; 
            pixels[curRGB_Triplet] = double(j) / imageWidth; // Setting Red channel
            pixels[curRGB_Triplet + 1] = double(i) / imageHeight; // Setting Green channel
            pixels[curRGB_Triplet + 2] = 0;
        }
    }

    RT_UTILITIES::writePPM("./imageOut.ppm", imageWidth, imageHeight, pixels);

    return 0;
}