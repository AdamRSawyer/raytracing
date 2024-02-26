//#define WIN_32
//#define LINUX
#define APPLE

#include <iostream>
#include "raytracer_Funcs.cpp"

void clearTerminal();
void drawProgressBar(float percComplete);

int main()
{
    uint16_t imageWidth = 256;
    uint16_t imageHeight = 256;

    double pixels[imageHeight * imageWidth * 3];

    for (int i = 0; i < imageHeight; ++i)
    {
        clearTerminal();
        drawProgressBar(float(i) / imageHeight);

        for (int j = 0; j < imageWidth; ++j)
        {
            uint64_t curRGB_Triplet = i * imageWidth * 3 + j * 3; 
            pixels[curRGB_Triplet] = double(j) / imageWidth; // Setting Red channel
            pixels[curRGB_Triplet + 1] = double(i) / imageHeight; // Setting Green channel
            pixels[curRGB_Triplet + 2] = 0;
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