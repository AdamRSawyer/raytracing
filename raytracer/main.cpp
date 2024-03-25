//#define WIN_32
//#define LINUX
#define APPLE

#include <iostream>
#include <cmath>

#include "Point3.h"
#include "Color.h"
#include "Ray.h"
#include "raytracer_Funcs.cpp"

#include "Utility.h"
#include "Hittable.h"
#include "Hittable_List.h"
#include "Sphere.h"
#include "Interval.h"
#include "Camera.h"

Color rayColor(const Ray& r, const Hittable_List& objcts);
Color rayColor(const Ray& r);
Color sphereIntersect(const Ray& r);

int main()
{
    // const double aspectRatio = 16.0/9.0;
    // uint16_t imageHeight = 256;
    // uint16_t imageWidth = (static_cast<uint16_t>(imageHeight * aspectRatio) > 1) ? static_cast<uint16_t>(imageHeight * aspectRatio) : 0;

    // double viewPortHeight = 2.0;
    // double viewPortWidth = viewPortHeight * (double(imageWidth) / imageHeight);

    // Point3 cameraCenter(0, 0, 0);
    // double focalLength = 1;

    // Vec3 viewPort_u(viewPortWidth, 0, 0); // Horizontal viewport vector
    // Vec3 viewPort_v(0, -viewPortHeight, 0); // Vertical viewport vector

    // Vec3 delta_u = viewPort_u / imageWidth;
    // Vec3 delta_v = viewPort_v / imageHeight;

    // Point3 Q = cameraCenter + Vec3(0, 0, -focalLength) - viewPort_u / 2 - viewPort_v / 2; // Upper left viewpoint corner
    // Point3 P_00 = Q + delta_u / 2 + delta_v / 2; // Top left pixel

    Camera cam;

    Color pixels[cam.imageHeight * cam.imageWidth];

    Hittable_List world(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));

    cam.Render(world, pixels);


    // for (int i = 0; i < imageHeight; ++i)
    // {
    //     clearTerminal();
    //     drawProgressBar(float(i) / imageHeight);

    //     for (int j = 0; j < imageWidth; ++j)
    //     {
    //         Point3 curPixlPos = P_00 + delta_u * j + delta_v * i;
    //         Ray curRay(cameraCenter, static_cast<Vec3>(curPixlPos - cameraCenter));
            
    //         uint64_t curRGB_Triplet = i * imageWidth + j; 
    //         pixels[curRGB_Triplet] = rayColor(curRay, world);
    //     }
    // }

    // clearTerminal();
    // drawProgressBar(1);

    RT_UTILITIES::writePPM("./imageOut.ppm", cam.imageWidth, cam.imageHeight, pixels);


    return 0;
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

// Just computes a blue-white gradient
Color rayColor(const Ray& r)
{
    // Create gradient based on y position from -1.0 to 1.0 going from blue to white
    Color blue(0.5, 0.7, 1);
    Color white(1, 1, 1);
    
    Point3 pos = unit_vector(r.origin() + r.direction());
    double a = (pos.v[1] + 1) / 2;
    Color out = (1 - a) * white + a * blue;

    return out;
}

Color sphereIntersect(const Ray& r)
{
    // Check if the ray intersects with a sphere centered at (0, 0, -1)

    Point3 c(0, 0, -1);
    double rad = 0.5;

    Point3 A = r.origin();
    Point3 b = r.direction();
    
    double quad_a = b.magnitude_sqrd();
    double quad_b = dot(b, A - c);
    double quad_c = (A - c).magnitude_sqrd() - rad * rad;

    double sqrt = pow(quad_b, 2) - (quad_a * quad_c);
    // Check if the square root of the quadratic formula is 0, < 0 or > 0
    if (sqrt < -__DBL_EPSILON__)
    {
        // No solution therefore no contact, thus compute the blue gradient
        return rayColor(r);
    } 
    else if (sqrt > __DBL_EPSILON__)
    {
        // 2 solutions therefore two contacts
        sqrt = sqrtl(sqrt);

        double sol_1 = (-quad_b + sqrt) / quad_a;
        double sol_2 = (-quad_b - sqrt) / quad_a;

        // We want the closer solution
        if (sol_1 < sol_2)
        {
            Point3 hp = r.at(sol_1);
            Point3 surfNorm = unit_vector((hp - c) / rad);

            return Color(surfNorm.v[0], surfNorm.v[1], surfNorm.v[2]);
        }
        else
        {
            Point3 hp = r.at(sol_2);
            Point3 surfNorm = unit_vector((hp - c) / rad);

            return 0.5*Color(surfNorm.v[0] + 1, surfNorm.v[1] + 1, surfNorm.v[2] + 1);
        }
    }
    else if (sqrt < __DBL_EPSILON__ && sqrt > __DBL_EPSILON__)
    {
        // One solution, just return red and put no extra computation here for now
        double sol = (-quad_b + sqrt) / quad_a;

        Point3 hp = r.at(sol);
        Point3 surfNorm = unit_vector((hp - c) / rad);

        return Color(surfNorm.v[0], surfNorm.v[1], surfNorm.v[2]);
    }
}