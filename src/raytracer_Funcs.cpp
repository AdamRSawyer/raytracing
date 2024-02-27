#include <string>
#include <iostream>
#include <fstream>
#include "Color.h"

namespace RT_UTILITIES {

    // Write image to disk in PPM format
    /*
        filePath: The full filepath including the filename at the end
        imageWidth: Number of columns in the image
        imageHeight: Number of rows in the image
        pixels: Array of RGB values from 0.0-1.0. The array should be of the size imageWidth * imageHeight * 3 (one value for each color channel)
                the pixel order is written out in rows starting at the top left and ending at the bottom right pixel
    */
    bool writePPM(std::string filePath, uint16_t imageWidth, uint16_t imageHeight, Color *pixels)
    {
        std::ofstream f(filePath.c_str(), std::ios::out);

        if(f.is_open())
        {
            // Write header of PPM file
            // P3 means the colors are in ASCII format and then on the next line the image width and height are written. 255 is the max color value 
            f << "P3\n" << imageWidth << ' ' << imageHeight << '\n' << "255\n";

            // Next all of the pixel values are written out
            for (int i = 0; i < imageHeight; ++i)
            {
                for (int j = 0; j < imageWidth; ++j)
                {
                    uint64_t curRGB_Triplet = i * imageWidth + j; 
                    f << pixels[curRGB_Triplet] << '\n';
                }
                
            }
            f.close();
            return true;
        }

        // Files failed to open
        return false;
    }

}