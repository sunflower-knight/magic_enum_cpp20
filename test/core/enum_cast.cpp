#include <doctest/doctest.h>

#include "resource.h"

#include <magic_enum/core/enum_cast.hpp>

using namespace magic_enum;
TEST_CASE("enum_cast") {
  SUBCASE("string") {
    constexpr auto cr = enum_cast<Color>("red");
    REQUIRE(cr.value() == Color::RED);
    REQUIRE(enum_cast<Color&>("GREEN").value() == Color::GREEN);
    // REQUIRE(enum_cast<Color>("blue", [](char lhs, char rhs) { return std::tolower(lhs) == std::tolower(rhs); }).value() == Color::BLUE);
    REQUIRE_FALSE(enum_cast<Color>("None").has_value());

    constexpr auto no = enum_cast<Numbers>("one");
    REQUIRE(no.value() == Numbers::one);
    REQUIRE(enum_cast<Numbers>("two").value() == Numbers::two);
    REQUIRE(enum_cast<Numbers>("three").value() == Numbers::three);
    REQUIRE_FALSE(enum_cast<Numbers>("many").has_value());
    REQUIRE_FALSE(enum_cast<Numbers>("None").has_value());

    constexpr auto dr = enum_cast<Directions>("Right");
    REQUIRE(enum_cast<Directions&>("Up").value() == Directions::Up);
    REQUIRE(enum_cast<const Directions>("Down").value() == Directions::Down);
    REQUIRE(dr.value() == Directions::Right);
    REQUIRE(enum_cast<Directions>("Left").value() == Directions::Left);
    REQUIRE_FALSE(enum_cast<Directions>("None").has_value());

    // constexpr auto dr2 = enum_cast<Directions>("RIGHT", case_insensitive);
    // REQUIRE(dr2.value() == Directions::Right);
    // REQUIRE(enum_cast<Directions&>("up", case_insensitive).value() == Directions::Up);
    // REQUIRE(enum_cast<const Directions>("dOwN", case_insensitive).value() == Directions::Down);
    // REQUIRE_FALSE(enum_cast<Directions>("Left-", case_insensitive).has_value());

    constexpr auto nt = enum_cast<number>("three");
    REQUIRE(enum_cast<number>("one").value() == number::one);
    REQUIRE(enum_cast<number>("two").value() == number::two);
    REQUIRE(nt.value() == number::three);
    REQUIRE_FALSE(enum_cast<number>("four").has_value());
    REQUIRE_FALSE(enum_cast<number>("None").has_value());

    REQUIRE(enum_cast<crc_hack>("b5a7b602ab754d7ab30fb42c4fb28d82").has_value());
    REQUIRE_FALSE(enum_cast<crc_hack>("d19f2e9e82d14b96be4fa12b8a27ee9f").has_value());

    constexpr auto crc = enum_cast<crc_hack_2>("b5a7b602ab754d7ab30fb42c4fb28d82");
    REQUIRE(crc.value() == crc_hack_2::b5a7b602ab754d7ab30fb42c4fb28d82);
    REQUIRE(enum_cast<crc_hack_2>("d19f2e9e82d14b96be4fa12b8a27ee9f").value() == crc_hack_2::d19f2e9e82d14b96be4fa12b8a27ee9f);

    REQUIRE(enum_cast<BoolTest>("Nay").has_value());
  }

  SUBCASE("integer") {
    Color cm[3] = {Color::RED, Color::GREEN, Color::BLUE};
    constexpr auto cr = enum_cast<Color>(-12);
    REQUIRE(cr.value() == Color::RED);
    REQUIRE(enum_cast<Color&>(7).value() == Color::GREEN);
    REQUIRE(enum_cast<Color>(static_cast<int>(cm[2])).value() == Color::BLUE);
    REQUIRE_FALSE(enum_cast<Color>(0).has_value());

    constexpr auto no = enum_cast<Numbers>(1);
    REQUIRE(no.value() == Numbers::one);
    REQUIRE(enum_cast<Numbers>(2).value() == Numbers::two);
    REQUIRE(enum_cast<Numbers>(3).value() == Numbers::three);
    REQUIRE_FALSE(enum_cast<Numbers>(127).has_value());
    REQUIRE_FALSE(enum_cast<Numbers>(0).has_value());

    constexpr auto dr = enum_cast<Directions>(120);
    REQUIRE(enum_cast<Directions&>(85).value() == Directions::Up);
    REQUIRE(enum_cast<const Directions>(-42).value() == Directions::Down);
    REQUIRE(dr.value() == Directions::Right);
    REQUIRE(enum_cast<Directions>(-120).value() == Directions::Left);
    REQUIRE_FALSE(enum_cast<Directions>(0).has_value());

    constexpr auto nt = enum_cast<number>(300);
    REQUIRE(enum_cast<number>(100).value() == number::one);
    REQUIRE(enum_cast<number>(200).value() == number::two);
    REQUIRE(nt.value() == number::three);
    REQUIRE_FALSE(enum_cast<number>(400).has_value());
    REQUIRE_FALSE(enum_cast<number>(0).has_value());

    REQUIRE(enum_cast<BoolTest>(false).has_value());
    REQUIRE(enum_cast<BoolTest>(0).has_value());
  }
}
