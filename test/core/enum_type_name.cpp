#include <doctest/doctest.h>

#include "resource.h"

#include <magic_enum/core/enum_type_name.hpp>

using namespace magic_enum;

TEST_CASE("enum_type_name") {
    REQUIRE(enum_type_name<Color&>() == "Color");
    REQUIRE(enum_type_name<const Numbers>() == "Numbers");
    REQUIRE(enum_type_name<const Directions&>() == "Directions");
    REQUIRE(enum_type_name<number>() == "number");

    REQUIRE(enum_type_name<lt1>() == "lt1");
    REQUIRE(enum_type_name<lt2>() == "lt2");
    REQUIRE(enum_type_name<lt3>() == "lt3");
    REQUIRE(enum_type_name<lt4>() == "lt4");
    REQUIRE(enum_type_name<foo1::lt5>() == "lt5");
    REQUIRE(enum_type_name<foo2::lt6>() == "lt6");
    REQUIRE(enum_type_name<decltype(foo2::s6)>() == "lt6");

    REQUIRE(enum_type_name<boo1::lt1>() == "lt1");
    REQUIRE(enum_type_name<boo1::lt2>() == "lt2");
    REQUIRE(enum_type_name<boo1::lt3>() == "lt3");
    REQUIRE(enum_type_name<boo1::lt4>() == "lt4");
    REQUIRE(enum_type_name<boo1::foo1::lt5>() == "lt5");
    REQUIRE(enum_type_name<boo1::foo2::lt6>() == "lt6");
    REQUIRE(enum_type_name<decltype(boo1::foo2::s6)>() == "lt6");

    REQUIRE(enum_type_name<boo2::boo3::lt1>() == "lt1");
    REQUIRE(enum_type_name<boo2::boo3::lt2>() == "lt2");
    REQUIRE(enum_type_name<boo2::boo3::lt3>() == "lt3");
    REQUIRE(enum_type_name<boo2::boo3::lt4>() == "lt4");
    REQUIRE(enum_type_name<boo2::boo3::foo1::lt5>() == "lt5");
    REQUIRE(enum_type_name<boo2::boo3::foo2::lt6>() == "lt6");
    REQUIRE(enum_type_name<decltype(boo2::boo3::foo2::s6)>() == "lt6");

    REQUIRE(enum_type_name<a_lt1>() == "a_lt1");
    REQUIRE(enum_type_name<a_lt2>() == "a_lt2");
    REQUIRE(enum_type_name<a_lt3>() == "a_lt3");
    REQUIRE(enum_type_name<a_lt4>() == "a_lt4");
    REQUIRE(enum_type_name<a_foo1::a_lt5>() == "a_lt5");
    REQUIRE(enum_type_name<a_foo2::a_lt6>() == "a_lt6");
    REQUIRE(enum_type_name<decltype(a_foo2::s6)>() == "a_lt6");
}
