#include "catch_amalgamated.hpp"
#include "core/vecmath.hpp"
#include "core/tfrt.hpp"

using Catch::Approx;

TEST_CASE("Vector addition and scaling", "[vecmath]") {
    tfrt::Vector3f a{1,2,3}, b{4,-1,0};
    auto c = a + b;
    REQUIRE(c.x == Approx(5.0f));
    REQUIRE(c.y == Approx(1.0f));
    REQUIRE(c.z == Approx(3.0f));

    auto d = a * 2.5f;
    REQUIRE(d.x == Approx(2.5f));
    REQUIRE(d.y == Approx(5.0f));
    REQUIRE(d.z == Approx(7.5f));
}

// …more TEST_CASEs for dot, cross, length, normalize, clamp, etc.
