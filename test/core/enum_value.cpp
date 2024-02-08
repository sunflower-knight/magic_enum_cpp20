#include <doctest/doctest.h>

#include "resource.h"

#include <magic_enum/core/enum_value.hpp>

using namespace magic_enum;
TEST_CASE("enum_value") {
    constexpr auto cr = enum_value<Color>(0);
    REQUIRE(cr == Color::RED);
    REQUIRE(enum_value<Color&>(1) == Color::GREEN);
    REQUIRE(enum_value<Color>(2) == Color::BLUE);

    REQUIRE(enum_value<Color, 0>() == Color::RED);
    REQUIRE(enum_value<Color, 1>() == Color::GREEN);
    REQUIRE(enum_value<Color, 2>() == Color::BLUE);

    constexpr auto no = enum_value<Numbers>(0);
    REQUIRE(no == Numbers::one);
    REQUIRE(enum_value<Numbers>(1) == Numbers::two);
    REQUIRE(enum_value<Numbers>(2) == Numbers::three);

    REQUIRE(enum_value<Numbers, 0>() == Numbers::one);
    REQUIRE(enum_value<Numbers, 1>() == Numbers::two);
    REQUIRE(enum_value<Numbers, 2>() == Numbers::three);

    constexpr auto dr = enum_value<Directions>(3);
    REQUIRE(enum_value<Directions&>(0) == Directions::Left);
    REQUIRE(enum_value<const Directions>(1) == Directions::Down);
    REQUIRE(enum_value<Directions>(2) == Directions::Up);
    REQUIRE(dr == Directions::Right);

    REQUIRE(enum_value<Directions, 0>() == Directions::Left);
    REQUIRE(enum_value<Directions, 1>() == Directions::Down);
    REQUIRE(enum_value<Directions, 2>() == Directions::Up);
    REQUIRE(enum_value<Directions, 3>() == Directions::Right);

    constexpr auto nt = enum_value<number>(2);
    REQUIRE(enum_value<number>(0) == number::one);
    REQUIRE(enum_value<number>(1) == number::two);
    REQUIRE(nt == number::three);

    REQUIRE(enum_value<number, 0>() == number::one);
    REQUIRE(enum_value<number, 1>() == number::two);
    REQUIRE(enum_value<number, 2>() == number::three);

    REQUIRE(enum_value<BoolTest>(0) == BoolTest::Yay);
    REQUIRE(enum_value<BoolTest, 0>() == BoolTest::Yay);
}

TEST_CASE("enum_values") {
    REQUIRE(std::is_same_v<decltype(enum_values<Color>()), const std::array<Color, 3>&>);

    constexpr auto& s1 = enum_values<Color&>();
    REQUIRE(s1 == std::array<Color, 3>{{Color::RED, Color::GREEN, Color::BLUE}});

    constexpr auto& s2 = enum_values<Numbers>();
    REQUIRE(s2 == std::array<Numbers, 3>{{Numbers::one, Numbers::two, Numbers::three}});

    constexpr auto& s3 = enum_values<const Directions>();
    REQUIRE(s3 == std::array<Directions, 4>{{Directions::Left, Directions::Down, Directions::Up, Directions::Right}});

    constexpr auto& s4 = enum_values<number>();
    REQUIRE(s4 == std::array<number, 3>{{number::one, number::two, number::three}});

    constexpr auto& s5 = enum_values<Binary>();
    REQUIRE(s5 == std::array<Binary, 2>{{Binary::ONE, Binary::TWO}});

    constexpr auto& s6 = enum_values<MaxUsedAsInvalid>();
    REQUIRE(s6 == std::array<MaxUsedAsInvalid, 2>{{MaxUsedAsInvalid::ONE, MaxUsedAsInvalid::TWO}});
}
