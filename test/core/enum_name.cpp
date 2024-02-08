#include <doctest/doctest.h>

#include "resource.h"

#include <magic_enum/core/enum_name.hpp>

using namespace magic_enum;

TEST_CASE("enum_name") {
  SUBCASE("automatic storage") {
    constexpr Color cr = Color::RED;
    constexpr auto cr_name = enum_name(cr);
    Color cm[3] = {Color::RED, Color::GREEN, Color::BLUE};
    Color cb = Color::BLUE;
    REQUIRE(cr_name == "red");
    REQUIRE(enum_name<Color&>(cb) == "BLUE");
    // REQUIRE(enum_name<as_flags<false>>(cm[1]) == "GREEN");
    // REQUIRE(enum_name<as_common<true>>(cm[1]) == "GREEN");
    // REQUIRE(enum_name<as_flags<false>>(static_cast<Color>(0)).empty());

    constexpr Numbers no = Numbers::one;
    constexpr auto no_name = enum_name(no);
    REQUIRE(no_name == "one");
    // REQUIRE(enum_name<Numbers, as_flags<false>>(Numbers::two) == "two");
    // REQUIRE(enum_name<as_flags<false>, Numbers>(Numbers::three) == "three");
    REQUIRE(enum_name(Numbers::many).empty());
    REQUIRE(enum_name(static_cast<Numbers>(0)).empty());

    constexpr Directions dr = Directions::Right;
    constexpr auto dr_name = enum_name(dr);
    Directions du = Directions::Up;
    REQUIRE(enum_name<Directions&>(du) == "Up");
    REQUIRE(enum_name<const Directions>(Directions::Down) == "Down");
    REQUIRE(dr_name == "Right");
    REQUIRE(enum_name(Directions::Left) == "Left");
    REQUIRE(enum_name(static_cast<Directions>(0)).empty());

    constexpr number nt = number::three;
    constexpr auto nt_name = enum_name(nt);
    REQUIRE(enum_name(number::one) == "one");
    REQUIRE(enum_name(number::two) == "two");
    REQUIRE(nt_name == "three");
    REQUIRE(enum_name(number::four).empty());
    REQUIRE(enum_name(static_cast<number>(0)).empty());

    REQUIRE(enum_name(MaxUsedAsInvalid::ONE) == "ONE");

    REQUIRE(enum_name(lt1::s1) == "s1");
    REQUIRE(enum_name(lt1::loooooooooooooooooooong1) == "loooooooooooooooooooong1");
    REQUIRE(enum_name(lt2::s2) == "s2");
    REQUIRE(enum_name(lt2::loooooooooooooooooooong2) == "loooooooooooooooooooong2");
    REQUIRE(enum_name(lt3::s3) == "s3");
    REQUIRE(enum_name(lt3::loooooooooooooooooooong3) == "loooooooooooooooooooong3");
    REQUIRE(enum_name(lt4::s4) == "s4");
    REQUIRE(enum_name(lt4::loooooooooooooooooooong4) == "loooooooooooooooooooong4");
    REQUIRE(enum_name(foo1::lt5::s5) == "s5");
    REQUIRE(enum_name(foo1::lt5::loooooooooooooooooooong5) == "loooooooooooooooooooong5");
    REQUIRE(enum_name(foo2::s6) == "s6");
    REQUIRE(enum_name(foo2::loooooooooooooooooooong6) == "loooooooooooooooooooong6");

    REQUIRE_FALSE(enum_name((foo1::lt5)12).size());
    REQUIRE_FALSE(enum_name((foo2::lt6)12).size());

    REQUIRE(enum_name(boo1::lt1::s1) == "s1");
    REQUIRE(enum_name(boo1::lt1::loooooooooooooooooooong1) == "loooooooooooooooooooong1");
    REQUIRE(enum_name(boo1::lt2::s2) == "s2");
    REQUIRE(enum_name(boo1::lt2::loooooooooooooooooooong2) == "loooooooooooooooooooong2");
    REQUIRE(enum_name(boo1::lt3::s3) == "s3");
    REQUIRE(enum_name(boo1::lt3::loooooooooooooooooooong3) == "loooooooooooooooooooong3");
    REQUIRE(enum_name(boo1::lt4::s4) == "s4");
    REQUIRE(enum_name(boo1::lt4::loooooooooooooooooooong4) == "loooooooooooooooooooong4");
    REQUIRE(enum_name(boo1::foo1::lt5::s5) == "s5");
    REQUIRE(enum_name(boo1::foo1::lt5::loooooooooooooooooooong5) == "loooooooooooooooooooong5");
    REQUIRE(enum_name(boo1::foo2::s6) == "s6");
    REQUIRE(enum_name(boo1::foo2::loooooooooooooooooooong6) == "loooooooooooooooooooong6");

    REQUIRE_FALSE(enum_name((boo1::foo1::lt5)12).size());
    REQUIRE_FALSE(enum_name((boo1::foo2::lt6)12).size());

    REQUIRE(enum_name(boo2::boo3::lt1::s1) == "s1");
    REQUIRE(enum_name(boo2::boo3::lt1::loooooooooooooooooooong1) == "loooooooooooooooooooong1");
    REQUIRE(enum_name(boo2::boo3::lt2::s2) == "s2");
    REQUIRE(enum_name(boo2::boo3::lt2::loooooooooooooooooooong2) == "loooooooooooooooooooong2");
    REQUIRE(enum_name(boo2::boo3::lt3::s3) == "s3");
    REQUIRE(enum_name(boo2::boo3::lt3::loooooooooooooooooooong3) == "loooooooooooooooooooong3");
    REQUIRE(enum_name(boo2::boo3::lt4::s4) == "s4");
    REQUIRE(enum_name(boo2::boo3::lt4::loooooooooooooooooooong4) == "loooooooooooooooooooong4");
    REQUIRE(enum_name(boo2::boo3::foo1::lt5::s5) == "s5");
    REQUIRE(enum_name(boo2::boo3::foo1::lt5::loooooooooooooooooooong5) == "loooooooooooooooooooong5");
    REQUIRE(enum_name(boo2::boo3::foo2::s6) == "s6");
    REQUIRE(enum_name(boo2::boo3::foo2::loooooooooooooooooooong6) == "loooooooooooooooooooong6");

    REQUIRE_FALSE(enum_name((boo2::boo3::foo1::lt5)12).size());
    REQUIRE_FALSE(enum_name((boo2::boo3::foo2::lt6)12).size());

    REQUIRE(enum_name(a_lt1::s1) == "s1");
    REQUIRE(enum_name(a_lt1::loooooooooooooooooooong1) == "loooooooooooooooooooong1");
    REQUIRE(enum_name(a_lt2::s2) == "s2");
    REQUIRE(enum_name(a_lt2::loooooooooooooooooooong2) == "loooooooooooooooooooong2");
    REQUIRE(enum_name(a_lt3::s3) == "s3");
    REQUIRE(enum_name(a_lt3::loooooooooooooooooooong3) == "loooooooooooooooooooong3");
    REQUIRE(enum_name(a_lt4::s4) == "s4");
    REQUIRE(enum_name(a_lt4::loooooooooooooooooooong4) == "loooooooooooooooooooong4");
    REQUIRE(enum_name(a_foo1::a_lt5::s5) == "s5");
    REQUIRE(enum_name(a_foo1::a_lt5::loooooooooooooooooooong5) == "loooooooooooooooooooong5");
    REQUIRE(enum_name(a_foo2::s6) == "s6");
    REQUIRE(enum_name(a_foo2::loooooooooooooooooooong6) == "loooooooooooooooooooong6");

    REQUIRE_FALSE(enum_name((a_foo1::a_lt5)12).size());
    REQUIRE_FALSE(enum_name((a_foo2::a_lt6)12).size());
  }

  SUBCASE("static storage") {
    constexpr Color cr = Color::RED;
    constexpr auto cr_name = enum_name<cr>();
    constexpr Color cm[3] = {Color::RED, Color::GREEN, Color::BLUE};
    REQUIRE(cr_name == "red");
    REQUIRE(enum_name<Color::BLUE>() == "BLUE");
    REQUIRE(enum_name<cm[1]>() == "GREEN");

    constexpr Numbers no = Numbers::one;
    constexpr auto no_name = enum_name<no>();
    REQUIRE(no_name == "one");
    REQUIRE(enum_name<Numbers::two>() == "two");
    REQUIRE(enum_name<Numbers::three>() == "three");
    REQUIRE(enum_name<Numbers::many>() == "many");

    constexpr Directions dr = Directions::Right;
    constexpr auto dr_name = enum_name<dr>();
    REQUIRE(enum_name<Directions::Up>() == "Up");
    REQUIRE(enum_name<Directions::Down>() == "Down");
    REQUIRE(dr_name == "Right");
    REQUIRE(enum_name<Directions::Left>() == "Left");

    constexpr number nt = number::three;
    constexpr auto nt_name = enum_name<nt>();
    REQUIRE(enum_name<number::one>() == "one");
    REQUIRE(enum_name<number::two>() == "two");
    REQUIRE(nt_name == "three");
    REQUIRE(enum_name<number::four>() == "four");

    REQUIRE(enum_name<Binary::ONE>() == "ONE");
    REQUIRE(enum_name<MaxUsedAsInvalid::ONE>() == "ONE");
  }

  SUBCASE("empty if the value is out of range")
  {
	LargeNumbers GENERATE[2] = {LargeNumbers::First, LargeNumbers::Second};
	for (const auto ln_value : GENERATE)
	{
		const auto ln_name = enum_name(ln_value);
		REQUIRE(ln_name.empty());
	}
  }
}

TEST_CASE("enum_names") {
	REQUIRE(std::is_same_v<decltype(enum_names<Color>()), const std::array<std::string_view, 3>&>);

	constexpr auto& s1 = enum_names<Color&>();
	REQUIRE(s1 == std::array<std::string_view, 3>{{"red", "GREEN", "BLUE"}});

	constexpr auto& s2 = enum_names<Numbers>();
	REQUIRE(s2 == std::array<std::string_view, 3>{{"one", "two", "three"}});

	constexpr auto& s3 = enum_names<const Directions>();
	REQUIRE(s3 == std::array<std::string_view, 4>{{"Left", "Down", "Up", "Right"}});

	constexpr auto& s4 = enum_names<number>();
	REQUIRE(s4 == std::array<std::string_view, 3>{{"one", "two", "three"}});
}
