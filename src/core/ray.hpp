#pragma once

#include "vecmath.hpp"

namespace tfrt
{
    class Ray
    {
    public:
        Point3f o;
        Vector3f d;
        float tMin, tMax;
        float time = 0;

        Ray() = default;
        Ray(const Point3f& o, const Vector3f& d, float time = 0)
            : o(o), d(d), time(time) {}

        Point3f operator()(float t) const { return o + d * t; }

        // std::string ToString() const {}
    };

    class RayDifferential : public Ray
    {
    public:
        bool hasDifferentials = false;
        Point3f rxOrigin, ryOrigin;
        Vector3f rxDirection, ryDirection;

        RayDifferential(Point3f o, Vector3f d, float time = 0) : Ray(o, d, time) {}
        explicit RayDifferential(const Ray& ray) : Ray(ray) {}
        void ScaleDifferential(float s) {
            rxOrigin = o + (rxOrigin - o) * s;
            ryOrigin = o + (ryOrigin - o) * s;
            rxDirection = d + (rxDirection - d) * s;
            ryDirection = d + (ryDirection - d) * s;
        }
    };
}
