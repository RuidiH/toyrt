#include <vector>
#include <ostream>

struct Vec3 {
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    void operator+=(float v) {
        x += v;
        y += v;
        z += v;
    }

    void operator-=(float v) {
        x -= v;
        y -= v;
        z -= v;
    }
};

Vec3 operator+(Vec3 a, Vec3 b) {
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator-(Vec3 a, Vec3 b) {
    return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

struct Ray {
    Vec3 pos;
    Vec3 dir;

    Ray() : pos(0, 0, 0), dir(0, 0, 1) {}
    Ray(Vec3 p, Vec3 t) : pos(p.x, p.y, p.z), dir(t - p) {}
};

struct Sphere {
    Vec3 p;
    float radius = 5;
    Vec3 color = Vec3(255, 0, 0);

    Sphere() {}
    Sphere(Vec3 p) : p(p.x, p.y, p.z) {}
};

void WritePPM(const char* filename, 
    std::vector<std::vector<Vec3>>& image, 
    const Sphere& sphere, 
    const int focal_length,
    const int working_distance,
    const int WIDTH,
    const int HEIGHT,
    const Vec3 camera) {
        int width_offset = WIDTH * 0.5;
        int height_offset = HEIGHT * 0.5;
        int pixel_x = 0.1; 
        int pixel_y = 0.1; 

        for (auto r = 0; r < WIDTH; r++) {
            for (auto c = 0; c < HEIGHT; c++) {
                // find correct pixel position
                int x_pos = (r - width_offset + 0.5) * pixel_x;
                int y_pos = (c + height_offset - 0.5) * pixel_y;
                Vec3 pixel_center(x_pos, y_pos, camera.z + focal_length);
                // gather color from ray and update image vector
            }
        }

        // write color information to .ppm file
    }

int main(int argc, char* argv[]) {

    // image properties
    const int WIDTH = 400;
    const int HEIGHT = 400;
    std::vector<std::vector<Vec3>> image;

    // write gray color in framebuffer as background
    for (uint32_t row = 0; row < WIDTH; row++) {
        std::vector<Vec3> curr;
        for (uint32_t col = 0; col < HEIGHT; col++) {
            curr.push_back(Vec3(128, 128, 128));
        }
        image.push_back(curr);
    }

    // camera
    Vec3 camPos(0, 0, -10);
    Vec3 target(0, 0, 0); // camera target position 
    int focal_length = 3;
    int working_distance = 2;

    // sphere
    Sphere s(Vec3(0,0,0)); // unit sphere at origin


    WritePPM("../output.ppm");

    return 0;
}