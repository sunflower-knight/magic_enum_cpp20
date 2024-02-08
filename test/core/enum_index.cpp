#include <doctest/doctest.h>

#include "resource.h"

#include <magic_enum/core/enum_index.hpp>

using namespace magic_enum;

TEST_CASE("enum_index") {
    Color cm[3] = {Color::RED, Color::GREEN, Color::BLUE};
    constexpr auto cr = enum_index(Color::RED);
    Color cg = Color::GREEN;
    REQUIRE(cr.value() == 0);
    REQUIRE(enum_index<Color::RED>() == 0);
    REQUIRE(enum_index<Color&>(cg).value() == 1);
    REQUIRE(enum_index(cm[2]).value() == 2);
    REQUIRE_FALSE(enum_index(static_cast<Color>(0)).has_value());

    constexpr auto no = enum_index(Numbers::one);
    REQUIRE(no.value() == 0);
    REQUIRE(enum_index<Numbers::one>() == 0);
    REQUIRE(enum_index(Numbers::two).value() == 1);
    REQUIRE(enum_index(Numbers::three).value() == 2);
    REQUIRE_FALSE(enum_index(Numbers::many).has_value());
    REQUIRE_FALSE(enum_index(static_cast<Numbers>(0)).has_value());

    constexpr auto dr = enum_index(Directions::Right);
    Directions dl = Directions::Left;
    REQUIRE(enum_index<Directions::Left>() == 0);
    REQUIRE(enum_index<Directions&>(dl).value() == 0);
    REQUIRE(enum_index<const Directions>(Directions::Down).value() == 1);
    REQUIRE(enum_index(Directions::Up).value() == 2);
    REQUIRE(dr.value() == 3);
    REQUIRE_FALSE(enum_index(static_cast<Directions>(0)).has_value());

    constexpr auto nt = enum_index(number::three);
    REQUIRE(enum_index<number::one>() == 0);
    REQUIRE(enum_index(number::one).value() == 0);
    REQUIRE(enum_index(number::two).value() == 1);
    REQUIRE(nt.value() == 2);
    REQUIRE_FALSE(enum_index(number::four).has_value());
    REQUIRE_FALSE(enum_index(static_cast<number>(0)).has_value());

    REQUIRE(enum_index<BoolTest::Yay>() == 0);
}
