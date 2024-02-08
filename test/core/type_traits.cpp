#include "resource.h"
#include <doctest/doctest.h>

#include <magic_enum/core/enum_concept.hpp>

using namespace magic_enum;

TEST_CASE("type_traits") {
    REQUIRE_FALSE(is_unscoped_enum_v<Color>);
    REQUIRE_FALSE(is_unscoped_enum_v<Numbers>);
    REQUIRE(is_unscoped_enum_v<Directions>);
    REQUIRE(is_unscoped_enum_v<number>);

    REQUIRE(is_scoped_enum_v<Color>);
    REQUIRE(is_scoped_enum_v<Numbers>);
    REQUIRE_FALSE(is_scoped_enum_v<Directions>);
    REQUIRE_FALSE(is_scoped_enum_v<number>);
}
