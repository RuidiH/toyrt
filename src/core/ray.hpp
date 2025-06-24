#pragma once

#include <string>

#include "vecmath.hpp"

namespace tfrt
{
    class Ray
    {
    public:
        Point3f o;
        Vector3f d;
        Float tMin, tMax;
        Float time = 0;

    public:
        bool HasNaN() const { return (o.HasNaN() || d.HasNaN()); }
        Ray() = default;
        Ray(Point3f o, Vector3f d, float time = 0)
            : o(o), d(d), time(time) {}

        Point3f operator()(float t) const { return o + d * t; }

        std::string ToString() const {
            return "";
        }
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
