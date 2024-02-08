#include <doctest/doctest.h>

#include "resource.h"

#include <magic_enum/core/enum_integer.hpp>

using namespace magic_enum;

TEST_CASE("enum_integer") {
    Color cm[3] = {Color::RED, Color::GREEN, Color::BLUE};
    constexpr auto cr = enum_integer(Color::RED);
    Color cg = Color::GREEN;
    REQUIRE(cr == -12);
    REQUIRE(enum_integer<Color&>(cg) == 7);
    REQUIRE(enum_integer(cm[2]) == 15);
    REQUIRE(enum_integer(static_cast<Color>(0)) == 0);

    constexpr auto no = enum_integer(Numbers::one);
    REQUIRE(no == 1);
    REQUIRE(enum_integer(Numbers::two) == 2);
    REQUIRE(enum_integer(Numbers::three) == 3);
    REQUIRE(enum_integer(Numbers::many) == 127);
    REQUIRE(enum_integer(static_cast<Numbers>(0)) == 0);

    constexpr auto dr = enum_integer(Directions::Right);
    Directions dl = Directions::Left;
    REQUIRE(enum_integer<Directions&>(dl) == -120);
    REQUIRE(enum_integer<const Directions>(Directions::Down) == -42);
    REQUIRE(enum_integer(Directions::Up) == 85);
    REQUIRE(dr == 120);
    REQUIRE(enum_integer(static_cast<Directions>(0)) == 0);

    constexpr auto nt = enum_integer(number::three);
    REQUIRE(enum_integer(number::one) == 100);
    REQUIRE(enum_integer(number::two) == 200);
    REQUIRE(nt == 300);
    REQUIRE(enum_integer(number::four) == 400);
    REQUIRE(enum_integer(static_cast<number>(0)) == 0);

    REQUIRE(enum_integer(BoolTest::Yay) == false);
}
