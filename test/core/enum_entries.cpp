#include <doctest/doctest.h>

#include "resource.h"

#include <magic_enum/core/enum_entries.hpp>

using namespace magic_enum;

TEST_CASE("enum_entries") {
    REQUIRE(std::is_same_v<decltype(enum_entries<Color>()), const std::array<std::pair<Color, std::string_view>, 3>&>);

    constexpr auto& s1 = enum_entries<Color&>();
    REQUIRE(s1 == std::array<std::pair<Color, std::string_view>, 3>{{{Color::RED, "red"}, {Color::GREEN, "GREEN"}, {Color::BLUE, "BLUE"}}});

    constexpr auto& s2 = enum_entries<Numbers>();
    REQUIRE(s2 == std::array<std::pair<Numbers, std::string_view>, 3>{{{Numbers::one, "one"}, {Numbers::two, "two"}, {Numbers::three, "three"}}});

    constexpr auto& s3 = enum_entries<Directions&>();
    REQUIRE(s3 == std::array<std::pair<Directions, std::string_view>, 4>{{{Directions::Left, "Left"}, {Directions::Down, "Down"}, {Directions::Up, "Up"}, {Directions::Right, "Right"}}});

    constexpr auto& s4 = enum_entries<number>();
    REQUIRE(s4 == std::array<std::pair<number, std::string_view>, 3>{{{number::one, "one"}, {number::two, "two"}, {number::three, "three"}}});
}
