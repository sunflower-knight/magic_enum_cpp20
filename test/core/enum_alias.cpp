#include <doctest/doctest.h>

#include "resource.h"

#include <magic_enum/core/enum_name.hpp>
#include <magic_enum/core/enum_integer.hpp>
#include <magic_enum/core/enum_cast.hpp>
#include <magic_enum/core/enum_contains.hpp>

using namespace magic_enum;
#if defined(MAGIC_ENUM_SUPPORTED_ALIASES)
TEST_CASE("aliases") {
  REQUIRE(enum_count<number>() == 3);

  REQUIRE(enum_name(number::one) == enum_name(number::_1));
  REQUIRE(enum_name(number::two) == enum_name(number::_2));
  REQUIRE(enum_name(number::three) == enum_name(number::_3));
  REQUIRE(enum_name(number::four) == enum_name(number::_4));

  REQUIRE(enum_integer(number::one) == enum_integer(number::_1));
  REQUIRE(enum_integer(number::two) == enum_integer(number::_2));
  REQUIRE(enum_integer(number::three) == enum_integer(number::_3));
  REQUIRE(enum_integer(number::four) == enum_integer(number::_4));

  REQUIRE_FALSE(enum_cast<number>("_1").has_value());
  REQUIRE_FALSE(enum_cast<number>("_2").has_value());
  REQUIRE_FALSE(enum_cast<number>("_3").has_value());
  REQUIRE_FALSE(enum_cast<number>("_4").has_value());
}
#endif

TEST_CASE("extrema") {
  enum class BadColor : std::uint64_t {
    RED,
    GREEN,
    YELLOW,
    // The value NONE is ignored (out of range).
    // However, it affects the value of min_v. When reflected_min_v was incorrect,
    // the presence of NONE caused miv_v to be equal to -1, which was then cast to unsigned,
    // leading to a value of 18446744073709551615 (numeric_limit_max of uint64_t).
    NONE = std::numeric_limits<std::uint64_t>::max()
  };

  REQUIRE(magic_enum::enum_name<BadColor>(BadColor::NONE).empty());
  REQUIRE_FALSE(enum_cast<BadColor>(std::numeric_limits<std::uint64_t>::max()).has_value());
  REQUIRE_FALSE(magic_enum::enum_contains<BadColor>(std::numeric_limits<std::uint64_t>::max()));
  REQUIRE_FALSE(magic_enum::enum_contains<BadColor>(BadColor::NONE));

  SUBCASE("min") {
    REQUIRE(magic_enum::customize::enum_range<BadColor>::min == MAGIC_ENUM_RANGE_MIN);
    // REQUIRE(magic_enum::detail::reflected_min<BadColor, as_common<>>() == 0);
    // REQUIRE(magic_enum::detail::min_v<BadColor, as_common<>> == 0);
    //
    REQUIRE(magic_enum::customize::enum_range<Color>::min == MAGIC_ENUM_RANGE_MIN);
    // REQUIRE(magic_enum::detail::reflected_min<Color, as_common<>>() == MAGIC_ENUM_RANGE_MIN);
    // REQUIRE(magic_enum::detail::min_v<Color, as_common<>> == -12);
    //
    REQUIRE(magic_enum::customize::enum_range<Numbers>::min == MAGIC_ENUM_RANGE_MIN);
    // REQUIRE(magic_enum::detail::reflected_min<Numbers, as_common<>>() == MAGIC_ENUM_RANGE_MIN);
    // REQUIRE(magic_enum::detail::min_v<Numbers, as_common<>> == 1);
    //
    REQUIRE(magic_enum::customize::enum_range<Directions>::min == MAGIC_ENUM_RANGE_MIN);
    // REQUIRE(magic_enum::detail::reflected_min<Directions, as_common<>>() == MAGIC_ENUM_RANGE_MIN);
    // REQUIRE(magic_enum::detail::min_v<Directions, as_common<>> == -120);
    //
    REQUIRE(magic_enum::customize::enum_range<number>::min == 100);
    // REQUIRE(magic_enum::detail::reflected_min<number, as_common<>>() == 100);
    // REQUIRE(magic_enum::detail::min_v<number, as_common<>> == 100);
    //
    // REQUIRE(magic_enum::detail::reflected_min<Binary, as_common<>>() == 0);
    // REQUIRE(magic_enum::detail::min_v<Binary, as_common<>> == false);
    //
    // REQUIRE(magic_enum::detail::reflected_min<MaxUsedAsInvalid, as_common<>>() == 0);
    // REQUIRE(magic_enum::detail::min_v<MaxUsedAsInvalid, as_common<>> == 0);
  }

  SUBCASE("max") {
    REQUIRE(magic_enum::customize::enum_range<BadColor>::max == MAGIC_ENUM_RANGE_MAX);
    // REQUIRE(magic_enum::detail::reflected_max<BadColor, as_common<>>() == MAGIC_ENUM_RANGE_MAX);
    // REQUIRE(magic_enum::detail::max_v<BadColor, as_common<>> == 2);
    //
    REQUIRE(magic_enum::customize::enum_range<Color>::max == MAGIC_ENUM_RANGE_MAX);
    // REQUIRE(magic_enum::detail::reflected_max<Color, as_common<>>() == MAGIC_ENUM_RANGE_MAX);
    // REQUIRE(magic_enum::detail::max_v<Color, as_common<>> == 15);
    //
    REQUIRE(magic_enum::customize::enum_range<Numbers>::max == MAGIC_ENUM_RANGE_MAX);
    // REQUIRE(magic_enum::detail::reflected_max<Numbers, as_common<>>() == MAGIC_ENUM_RANGE_MAX);
    // REQUIRE(magic_enum::detail::max_v<Numbers, as_common<>> == 3);
    //
    REQUIRE(magic_enum::customize::enum_range<Directions>::max == MAGIC_ENUM_RANGE_MAX);
    // REQUIRE(magic_enum::detail::reflected_max<Directions, as_common<>>() == MAGIC_ENUM_RANGE_MAX);
    // REQUIRE(magic_enum::detail::max_v<Directions, as_common<>> == 120);
    //
    REQUIRE(magic_enum::customize::enum_range<number>::max == 300);
    // REQUIRE(magic_enum::detail::reflected_max<number, as_common<>>() == 300);
    // REQUIRE(magic_enum::detail::max_v<number, as_common<>> == 300);
    //
    // REQUIRE(magic_enum::detail::reflected_max<Binary, as_common<>>() == 1);
    // REQUIRE(magic_enum::detail::max_v<Binary, as_common<>> == true);
    //
    // REQUIRE(magic_enum::detail::reflected_max<MaxUsedAsInvalid, as_common<>>() == 64);
    // REQUIRE(magic_enum::detail::max_v<MaxUsedAsInvalid, as_common<>> == 63);
  }
}
