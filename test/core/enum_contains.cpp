#include <doctest/doctest.h>

#include "resource.h"

#include <magic_enum/core/enum_contains.hpp>

using namespace magic_enum;

TEST_CASE("enum_contains") {
  SUBCASE("value") {
    Color cm[3] = {Color::RED, Color::GREEN, Color::BLUE};
    constexpr auto cr = enum_contains(Color::RED);
    Color cg = Color::GREEN;
    REQUIRE(cr);
    REQUIRE(enum_contains<Color&>(cg));
    REQUIRE(enum_contains(cm[2]));
    REQUIRE_FALSE(enum_contains(static_cast<Color>(0)));

    constexpr auto no = enum_contains(Numbers::one);
    REQUIRE(no);
    REQUIRE(enum_contains(Numbers::two));
    REQUIRE(enum_contains(Numbers::three));
    REQUIRE_FALSE(enum_contains(Numbers::many));
    REQUIRE_FALSE(enum_contains(static_cast<Numbers>(0)));

    constexpr auto dr = enum_contains(Directions::Right);
    Directions dl = Directions::Left;
    REQUIRE(enum_contains<Directions&>(dl));
    REQUIRE(enum_contains<const Directions>(Directions::Down));
    REQUIRE(enum_contains(Directions::Up));
    REQUIRE(dr);
    REQUIRE_FALSE(enum_contains(static_cast<Directions>(0)));

    constexpr auto nt = enum_contains(number::three);
    REQUIRE(enum_contains(number::one));
    REQUIRE(enum_contains<number&>(number::two));
    REQUIRE(nt);
    REQUIRE_FALSE(enum_contains(number::four));
    REQUIRE_FALSE(enum_contains(static_cast<number>(0)));

    // REQUIRE(enum_contains(BoolTest::Yay));
  }

  SUBCASE("integer") {
    REQUIRE(enum_contains<Color>(-12));
    REQUIRE(enum_contains<Color&>(7));
    REQUIRE(enum_contains<Color>(15));
    REQUIRE_FALSE(enum_contains<Color>(42));
    REQUIRE_FALSE(enum_contains<Color>(-120));
    REQUIRE_FALSE(enum_contains<Color>(0));

    constexpr auto no = enum_integer(Numbers::one);
    REQUIRE(enum_contains<Numbers>(no));
    REQUIRE(enum_contains<Numbers>(enum_integer(Numbers::two)));
    REQUIRE(enum_contains<Numbers>(enum_integer(Numbers::three)));
    REQUIRE_FALSE(enum_contains<Numbers>(enum_integer(Numbers::many)));

    constexpr auto dr = enum_integer(Directions::Right);
    REQUIRE(enum_contains<Directions&>(dr));
    REQUIRE(enum_contains<const Directions>(Directions::Down));
    REQUIRE(enum_contains<Directions>(Directions::Up));
    REQUIRE_FALSE(enum_contains<Directions>(static_cast<Directions>(0)));

    constexpr auto nt = enum_contains<number>(number::three);
    REQUIRE(enum_contains<number>(number::one));
    REQUIRE(enum_contains<number>(100));
    REQUIRE(enum_contains<number>(200));
    REQUIRE(enum_contains<number>(300));
    REQUIRE(enum_contains<number>(number::two));
    REQUIRE(nt);
    REQUIRE_FALSE(enum_contains<number>(number::four));
    REQUIRE_FALSE(enum_contains<number>(111));
    REQUIRE_FALSE(enum_contains<number>(0));

    // REQUIRE(enum_contains<BoolTest>(false));
    // REQUIRE(enum_contains<BoolTest>(0));
  }

  SUBCASE("string") {
    constexpr auto cr = "red";
    REQUIRE(enum_contains<Color>(cr));
    REQUIRE(enum_contains<Color&>("GREEN"));
    // REQUIRE(enum_contains<Color>("blue", [](char lhs, char rhs) { return std::tolower(lhs) == std::tolower(rhs); }));
    REQUIRE_FALSE(enum_contains<Color>("None"));

    constexpr auto no = std::string_view{"one"};
    REQUIRE(enum_contains<Numbers>(no));
    REQUIRE(enum_contains<Numbers>("two"));
    REQUIRE(enum_contains<Numbers>("three"));
    REQUIRE_FALSE(enum_contains<Numbers>("many"));
    REQUIRE_FALSE(enum_contains<Numbers>("None"));

    auto dr = std::string{"Right"};
    REQUIRE(enum_contains<Directions&>("Up"));
    REQUIRE(enum_contains<Directions>("Down"));
    REQUIRE(enum_contains<const Directions>(dr));
    REQUIRE(enum_contains<Directions>("Left"));
    REQUIRE_FALSE(enum_contains<Directions>("None"));

    auto dr2 = std::string{"RIGHT"};
    // REQUIRE(enum_contains<const Directions>(dr2, case_insensitive));
    // REQUIRE(enum_contains<Directions&>("up", case_insensitive));
    // REQUIRE(enum_contains<Directions>("dOwN", case_insensitive));
    // REQUIRE_FALSE(enum_contains<Directions>("Left-", case_insensitive));

    constexpr auto nt = enum_contains<number>("three");
    REQUIRE(enum_contains<number>("one"));
    REQUIRE(enum_contains<number>("two"));
    REQUIRE(nt);
    REQUIRE_FALSE(enum_contains<number>("four"));
    REQUIRE_FALSE(enum_contains<number>("None"));

    REQUIRE(enum_contains<BoolTest>("Yay"));
  }
}
