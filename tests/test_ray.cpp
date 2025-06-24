#include <catch2/catch_test_macros.hpp>
#include "core/ray.hpp"
#include "core/vecmath.hpp"

// Test Ray::at()
// TEST_CASE("Ray::at() computes correct point", "[ray]") {
//     Ray r{Point3f{0,0,0}, Vector3f{1,2,3}, 100.0f};
//     auto p = r.at(2.0f);
//     REQUIRE(p.x == Approx(2.0f));
//     REQUIRE(p.y == Approx(4.0f));
//     REQUIRE(p.z == Approx(6.0f));
// }

// Test Sphere intersection (assuming you have Sphere::intersect)
// TEST_CASE("Sphere intersection returns correct t0/t1", "[intersection]") {
//     Sphere s{Point3f{0,0,0}, 1.0f};
//     Ray r{Point3f{0,0,-5}, Vector3f{0,0,1}, 100.0f};
//     float t0, t1;
//     bool hit = s.intersect(r, &t0, &t1);
//     REQUIRE(hit);
//     REQUIRE(t0 == Approx(4.0f));
//     REQUIRE(t1 == Approx(6.0f));
// }
