#ifndef CAMERA_H
#define CAMERA_H

#include <cstdint>
#include <math.h>
#include "Utility.h"

#include "Hittable.h"
#include "Hittable_List.h"
#include "Sphere.h"
#include "Material.h"


class Camera
{
    public:
        double focalLength, aspectRatio, viewPortHeight, viewPortWidth;
        uint16_t imageHeight, imageWidth;
        uint16_t samplesPerPxl, maxDepth = 50;
        uint16_t hFov = 110;
        uint16_t vFov = 90;

        Point3 camCntr;
        Vec3 camAng;

        Camera() : focalLength(1), aspectRatio(16.0/9.0), imageHeight(400), samplesPerPxl(100), camCntr(Point3(-2, 2, 1)), camAng(Vec3(-9.1, -9.1, 0)) { initialize(); }

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
                        pixels[curRGB_Triplet] += rayColor(getRay(i, j), objects, 0);
                    }
                    pixels[curRGB_Triplet] /= samplesPerPxl;
                    pixels[curRGB_Triplet].clrClamp();
                    pixels[curRGB_Triplet].linear_to_gamma();
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
            
            //viewPortWidth = viewPortHeight * (double(imageWidth) / imageHeight);

            viewPortHeight = 2 * focalLength * tan(deg_to_rad(vFov) / 2);
            viewPortWidth = 2 * focalLength * tan(deg_to_rad(hFov) / 2);

            viewPort_u = rotate(Vec3(viewPortWidth, 0, 0), camAng); // Horizontal viewport vector
            viewPort_v = rotate(Vec3(0, -viewPortHeight, 0), camAng); // Vertical viewport vector

            delta_u = viewPort_u / imageWidth;
            delta_v = viewPort_v / imageHeight;
            
            Q = camCntr + rotate(Vec3(0, 0, -focalLength), camAng) - viewPort_u / 2 - viewPort_v / 2; // Upper left viewpoint corner
            P_00 = Q + delta_u / 2 + delta_v / 2; // Top left pixel
        }

        Ray getRay(uint16_t pxl_row, uint16_t pxl_col)
        {   

            Point3 curPixlPos = P_00 + delta_u * pxl_col + delta_v * pxl_row + pixelSampleSquare();
            bool cmplt = false;
            
            return Ray(camCntr, static_cast<Vec3>(curPixlPos - camCntr));
        }

        Vec3 pixelSampleSquare() const
        {
            return (-0.5 + random_double()) * delta_u + (-0.5 + random_double()) * delta_v;
        }

        Color rayColor(const Ray& r, const Hittable_List& objcts, uint16_t depth)
        {

            if (depth == maxDepth)
                return Color(0, 0, 0);

            Hit_Record hr;
            if(objcts.hit(r, Interval(0.001, INF), hr))
            {
                Color attenuation;
                Ray scattered(r);

                if(hr.mat->scatter(r, hr, attenuation, scattered))
                {
                    return attenuation * rayColor(scattered, objcts, depth + 1);
                }
                
                return Color(0.0, 0.0, 0.0);

            }

            // Create gradient based on y position from -1.0 to 1.0 going from blue to white
            Color blue(0.5, 0.7, 1.0);
            Color white(1.0, 1.0, 1.0);
            
            Point3 pos = unit_vector(r.direction());
            double a = (pos.v[1] + 1.0) / 2;
            Color out = (1.0 - a) * white + a * blue;

            return out;
        }



};

#endif