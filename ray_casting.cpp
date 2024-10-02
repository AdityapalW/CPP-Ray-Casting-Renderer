#include <iostream>
#include <cmath>
#include <fstream>

// Vector class for 3D operations
class Vec3 {
public:
    float x, y, z;
    
    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    
    // Vector addition
    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    // Vector subtraction
    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication
    Vec3 operator*(float scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    // Dot product
    float dot(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Normalize vector
    Vec3 normalize() const {
        float length = std::sqrt(x * x + y * y + z * z);
        return Vec3(x / length, y / length, z / length);
    }
};

// Ray class
class Ray {
public:
    Vec3 origin, direction;

    Ray(const Vec3& origin, const Vec3& direction) : origin(origin), direction(direction) {}
};

// Sphere class
class Sphere {
public:
    Vec3 center;
    float radius;
    
    Sphere(const Vec3& center, float radius) : center(center), radius(radius) {}
    
    // Ray-sphere intersection
    bool intersect(const Ray& ray, float& t) const {
        Vec3 oc = ray.origin - center;
        float a = ray.direction.dot(ray.direction);
        float b = 2.0f * oc.dot(ray.direction);
        float c = oc.dot(oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        
        if (discriminant < 0) return false;
        t = (-b - std::sqrt(discriminant)) / (2.0f * a);
        return true;
    }
};

// Write the image to a PPM file
void write_ppm(const std::string& filename, int width, int height, const Vec3* framebuffer) {
    std::ofstream ofs(filename, std::ios::out | std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    
    for (int i = 0; i < width * height; ++i) {
        unsigned char r = static_cast<unsigned char>(std::min(1.0f, framebuffer[i].x) * 255);
        unsigned char g = static_cast<unsigned char>(std::min(1.0f, framebuffer[i].y) * 255);
        unsigned char b = static_cast<unsigned char>(std::min(1.0f, framebuffer[i].z) * 255);
        ofs << r << g << b;
    }
    
    ofs.close();
}

// Main ray-casting logic
int main() {
    const int width = 800;
    const int height = 600;
    const float fov = 90.0f;
    
    Vec3* framebuffer = new Vec3[width * height];
    Sphere sphere(Vec3(0, 0, -5), 1.0f);  // Sphere at (0, 0, -5) with radius 1
    
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            float x = (2 * (i + 0.5f) / (float)width - 1) * tan(fov / 2 * M_PI / 180);
            float y = (1 - 2 * (j + 0.5f) / (float)height) * tan(fov / 2 * M_PI / 180);
            Vec3 direction = Vec3(x, y, -1).normalize();
            
            Ray ray(Vec3(0, 0, 0), direction);
            float t;
            
            if (sphere.intersect(ray, t)) {
                framebuffer[j * width + i] = Vec3(1, 0, 0);  // Red color for the sphere
            } else {
                framebuffer[j * width + i] = Vec3(0.2, 0.7, 1.0);  // Background color (sky blue)
            }
        }
    }
    
    write_ppm("output.ppm", width, height, framebuffer);
    delete[] framebuffer;
    
    return 0;
}
