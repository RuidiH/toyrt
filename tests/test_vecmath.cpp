#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "core/vecmath.hpp"
#include "core/tfrt.hpp"

using namespace Catch::Matchers;

/**
 * ---------------- Vector2 Test -------------------
 */

TEST_CASE("Vector2 addtion", "[Vector2]") {}

TEST_CASE("Vector2 subtraction", "[Vector2]") {}

TEST_CASE("Vector2 scale", "[Vector2]") {}

TEST_CASE("Vector2 division", "[Vector2]") {}

TEST_CASE("Vector2 dot", "[Vector2]") {}

TEST_CASE("Vector2 absdot", "[Vector2]") {}

TEST_CASE("Vector2 length squared", "[Vector2]") {}

TEST_CASE("Vector2 length", "[Vector2]") {}

TEST_CASE("Vector2 distance", "[Vector2]") {}

TEST_CASE("Vector2 distance squared", "[Vector2]") {}


/**
 * ---------------- Vector3 Test -------------------
 */

TEST_CASE("Vector3 addition and scaling", "[vecmath]") {
    tfrt::Vector3f a{1,2,3}, b{4,-1,0};
    auto c = a + b;
    REQUIRE_THAT(c.x, WithinULP(5.0f, 0));
    REQUIRE_THAT(c.z, WithinULP(3.0f, 0));

    auto d = a * 2.5f;
    REQUIRE_THAT(d.x, WithinULP(2.5f, 0));
    REQUIRE_THAT(d.y, WithinULP(5.0f, 0));
    REQUIRE_THAT(d.z, WithinULP(7.5f, 0));
}

TEST_CASE("Vector3 addtion", "[Vector3]") {}

TEST_CASE("Vector3 subtraction", "[Vector3]") {}

TEST_CASE("Vector3 scale", "[Vector3]") {}

TEST_CASE("Vector3 division", "[Vector3]") {}

TEST_CASE("Vector3 dot", "[Vector3]") {}

TEST_CASE("Vector3 absdot", "[Vector3]") {}

TEST_CASE("Vector3 cross", "[Vector3]") {}

TEST_CASE("Vector3 length squared", "[Vector3]") {}

TEST_CASE("Vector3 length", "[Vector3]") {}

TEST_CASE("Vector3 distance", "[Vector3]") {}

TEST_CASE("Vector3 distance squared", "[Vector3]") {}

// …more TEST_CASEs for dot, cross, length, normalize, clamp, etc.


/**
 * ---------------- Point2 Test -------------------
 */

/**
 * ---------------- Point3 Test -------------------
 */