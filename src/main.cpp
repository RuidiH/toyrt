#include <vector>
#include <ostream>
#include <iostream>
#include <fstream>
#include <string>

#include <cmath>
#include <cstdint>

#include "core/vecmath.hpp"

struct Vec3
{
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    void operator+=(float v)
    {
        x += v;
        y += v;
        z += v;
    }

    void operator-=(float v)
    {
        x -= v;
        y -= v;
        z -= v;
    }
};

Vec3 normalize_vec3(Vec3 v) {
    float magnitude = 1 / std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return Vec3(v.x * magnitude, v.y * magnitude, v.z * magnitude);
}

std::string vec3_to_string(Vec3 v) {
    return std::to_string(v.x) + " " + 
        std::to_string(v.y) + " " + 
        std::to_string(v.z);
}

Vec3 operator+(Vec3 a, Vec3 b)
{
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(Vec3 a, Vec3 b)
{
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

struct Ray
{
    Vec3 pos;
    Vec3 dir;

    Ray() : pos(0, 0, 0), dir(0, 0, 1) {}
    Ray(Vec3 p, Vec3 t) : pos(p.x, p.y, p.z), dir(t - p) {}
};


struct Sphere
{
    Vec3 p;
    float radius = 5;
    Vec3 color = Vec3(255, 0, 0);

    Sphere() {}
    Sphere(Vec3 p, float r) : p(p.x, p.y, p.z), radius(r) {}
};

bool isIntersect(const Sphere& s, const Ray& r)
{
    // assuming sphere is sitting at the center of the world.

    // solve quadratic formula
    float dx = r.dir.x;
    float dy = r.dir.y;
    float dz = r.dir.z;
    float ox = r.pos.x;
    float oy = r.pos.y;
    float oz = r.pos.z;

    float a = dx * dx + dy * dy + dz * dz;
    float b = 2 * (ox * dx + oy * dy + oz * dz);
    float c = ox * ox + oy * oy + oz * oz - s.radius * s.radius;

    // compute the 3 terms of quadratic formula
    // float t1 = -b;
    float t2 = b * b - 4 * a * c;
    // std::cout << "t2: " << std::to_string(t2) << "\n";
    // no hit
    if (t2 < 0)
        return false;
    else
        return true;

    // no need to solve the t for current simple scene with one bounce.

    // float t3 = 0.5 * 1/a;

    // float tp = (t1 + t2) * t3;
    // float tn = (t1 - t2) * t3;
    // float t_final = std::min(tp, tn);
    return true;
}

void WritePPM(const char *filename,
              std::vector<std::vector<Vec3>> &image,
              const Sphere &sphere,
              const int focal_length,
              const int WIDTH,
              const int HEIGHT,
              const Vec3 camera_pos)
{
    float width_offset = WIDTH * 0.5;
    float height_offset = HEIGHT * 0.5;
    // pixel width and height
    float pixel_x = 0.1;
    float pixel_y = 0.1;

    for (int r = 0; r < WIDTH; r++)
    {
        for (int c = 0; c < HEIGHT; c++)
        {
            // find correct pixel position
            float x_offset = (-width_offset + 0.5 + r) * pixel_x; 
            float y_offset = (height_offset - 0.5 - c) * pixel_y; 
            float x_pos = x_offset + camera_pos.x;
            float y_pos = y_offset + camera_pos.y;
            Vec3 pixel_center(x_pos, y_pos, camera_pos.z + focal_length);

            // std::cout << vec3_to_string(pixel_center) << std::endl;
            // std::cout << x_offset << " " << y_offset << "\n";

            // gather color from ray and update image vector
            // calculate current ray direction
            Vec3 dir = pixel_center - camera_pos;
            Ray ray;
            ray.pos = pixel_center;
            ray.dir = normalize_vec3(dir);
            // std::cout << vec3_to_string(pixel_center) 
                // << ", " << vec3_to_string(camera_pos) << "\n";
            // std::cout << vec3_to_string(ray.dir) << "\n";
            // determine if ray hits an object
            if (isIntersect(sphere, ray) == true)
            {
                image[r][c] = sphere.color;
            }
        }
    }

    // write color information to .ppm file
    std::ofstream out("output.ppm", std::ofstream::trunc);
    if (!out.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    out << "P3\n";
    out << WIDTH << " " << HEIGHT << "\n";
    out << "255\n";

    for (auto r = 0; r < WIDTH; r++)
    {
        for (auto c = 0; c < HEIGHT; c++)
        {
            out << image[r][c].x << " "
                << image[r][c].y << " "
                << image[r][c].z << "\n";
        }
    }
    out.close(); 
    std::cout << "successfully write to file.\n";
}

int main()
{
    int* test = new int[3]{1, 2, 3};
    std::cout << "test " << test << std::endl;
    std::cout << "test[0] " << test[0] << std::endl;
    std::cout << "test[1] " << test[1] << std::endl;
    delete[] test;

    // image properties
    const int WIDTH = 400;
    const int HEIGHT = 400;
    std::vector<std::vector<Vec3>> image;

    // write gray color in framebuffer as background
    for (uint32_t row = 0; row < WIDTH; row++)
    {
        std::vector<Vec3> curr;
        for (uint32_t col = 0; col < HEIGHT; col++)
        {
            curr.push_back(Vec3(128, 128, 128));
        }
        image.push_back(curr);
    }

    // camera
    Vec3 camPos(0, 0, -8);
    Vec3 target(0, 0, 0); // camera target position
    int focal_length = 3;

    // sphere
    Sphere s(Vec3(0, 0, 0), 3); // unit sphere at origin

    WritePPM("../output.ppm", 
            image, 
            s, 
            focal_length, 
            WIDTH, 
            HEIGHT, 
            camPos);

    return 0;
}