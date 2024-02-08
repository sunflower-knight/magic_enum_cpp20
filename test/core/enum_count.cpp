#include <doctest/doctest.h>

#include "resource.h"

#include <magic_enum/core/enum_count.hpp>

using namespace magic_enum;

TEST_CASE("enum_count") {
    constexpr auto s1 = enum_count<Color&>();
    REQUIRE(s1 == 3);

    constexpr auto s2 = enum_count<Numbers>();
    REQUIRE(s2 == 3);

    constexpr auto s3 = enum_count<const Directions>();
    REQUIRE(s3 == 4);

    constexpr auto s4 = enum_count<number>();
    REQUIRE(s4 == 3);

    constexpr auto s5 = enum_count<Binary>();
    REQUIRE(s5 == 2);

    constexpr auto s6 = enum_count<MaxUsedAsInvalid>();
    REQUIRE(s6 == 2);
}
