#ifndef CAMERA_H
#define CAMERA_H

#include <cstdint>
#include "Utility.h"

#include "Hittable.h"
#include "Hittable_List.h"
#include "Sphere.h"


class Camera
{
    public:
        double focalLength, aspectRatio, viewPortHeight, viewPortWidth;
        uint16_t imageHeight, imageWidth;
        Point3 camCntr;
        uint16_t samplesPerPxl;

        Camera() : focalLength(1), aspectRatio(16.0/9.0), viewPortHeight(2), imageHeight(256), samplesPerPxl(10) { initialize(); }

        void setAspectRatio(double newAspectRatio)
        {
            aspectRatio = newAspectRatio;
            initialize();
        }

        void setImageHeight(uint16_t newImageHeight)
        {
            imageHeight = newImageHeight;
            initialize();
        }

        // Render assumes the pixels buffer is the size of imageHeight * imageWidth
        void Render(const Hittable_List& objects, Color pixels[])
        {
            for (int i = 0; i < imageHeight; ++i)
            {
                clearTerminal();
                drawProgressBar(float(i) / imageHeight);

                for (int j = 0; j < imageWidth; ++j)
                {
                    uint64_t curRGB_Triplet = i * imageWidth + j;
                    pixels[curRGB_Triplet] = Color(0, 0, 0);

                    for (int k = 0; k < samplesPerPxl; ++k)
                    {
                        pixels[curRGB_Triplet] += rayColor(getRay(i, j), objects);
                    }
                    pixels[curRGB_Triplet] /= samplesPerPxl;
                    pixels[curRGB_Triplet].clrClamp();
                }
            }

            clearTerminal();
            drawProgressBar(1);
        }
    
    private:
        Vec3 viewPort_u, viewPort_v, delta_u, delta_v;
        Point3 Q, P_00;


        void initialize()
        {
            imageWidth = (static_cast<uint16_t>(imageHeight * aspectRatio) > 1) ? static_cast<uint16_t>(imageHeight * aspectRatio) : 0;
            viewPortWidth = viewPortHeight * (double(imageWidth) / imageHeight);

            viewPort_u = Vec3(viewPortWidth, 0, 0); // Horizontal viewport vector
            viewPort_v = Vec3(0, -viewPortHeight, 0); // Vertical viewport vector

            delta_u = viewPort_u / imageWidth;
            delta_v = viewPort_v / imageHeight;

            Q = camCntr + Vec3(0, 0, -focalLength) - viewPort_u / 2 - viewPort_v / 2; // Upper left viewpoint corner
            P_00 = Q + delta_u / 2 + delta_v / 2; // Top left pixel
        }

        Ray getRay(uint16_t pxl_row, uint16_t pxl_col)
        {   

            Point3 curPixlPos = P_00 + delta_u * pxl_col + delta_v * pxl_row + pixelSampleSquare();
            return Ray(camCntr, static_cast<Vec3>(curPixlPos - camCntr));
        }

        Vec3 pixelSampleSquare()
        {
            return (-0.5 + random_double()) * delta_u + (-0.5 + random_double()) * delta_v;
        }

        Color rayColor(const Ray& r, const Hittable_List& objcts)
        {
            Hit_Record hr;
            if(objcts.hit(r, Interval(0, INF), hr))
            {
                Color out(hr.normal.v[0] + 1, hr.normal.v[1] + 1, hr.normal.v[2] + 1);
                return 0.5 * out;
            }

            // Create gradient based on y position from -1.0 to 1.0 going from blue to white
            Color blue(0.5, 0.7, 1);
            Color white(1, 1, 1);
            
            Point3 pos = unit_vector(r.origin() + r.direction());
            double a = (pos.v[1] + 1) / 2;
            Color out = (1 - a) * white + a * blue;

            return out;
        }



};

#endif