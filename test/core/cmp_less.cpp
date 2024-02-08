#include <doctest/doctest.h>

#include "resource.h"

#include <magic_enum/core/enum_name.hpp>
#include <magic_enum/core/enum_cast.hpp>

TEST_CASE("cmp_less") {
  using magic_enum::detail::cmp_less;

  constexpr std::uint64_t uint64_t_min = std::numeric_limits<std::uint64_t>::min();
  constexpr std::uint32_t uint32_t_min = std::numeric_limits<std::uint32_t>::min();
  constexpr std::uint32_t uint32_t_max = std::numeric_limits<std::uint32_t>::max();
  constexpr std::uint64_t uint64_t_max = std::numeric_limits<std::uint64_t>::max();

  constexpr std::int64_t int64_t_min = std::numeric_limits<std::int64_t>::min();
  constexpr std::int32_t int32_t_min = std::numeric_limits<std::int32_t>::min();
  constexpr std::int32_t int32_t_max = std::numeric_limits<std::int32_t>::max();
  constexpr std::int64_t int64_t_max = std::numeric_limits<std::int64_t>::max();

  // Also testing with offset to avoid corner cases.
  // Two variables to avoid hidden casts:
  constexpr std::int64_t offset_int64_t = 17;
  constexpr std::int32_t offset_int32_t = 17;

  SUBCASE("same signedness") {
    REQUIRE(cmp_less(-5, -3));
    REQUIRE(cmp_less(27U, 49U));
  }

  SUBCASE("same signedness, different width") {
    REQUIRE(cmp_less(uint32_t_max, uint64_t_max));
    REQUIRE_FALSE(cmp_less(uint64_t_max, uint32_t_max));
    REQUIRE(cmp_less(int64_t_min, int32_t_min));
    REQUIRE_FALSE(cmp_less(int32_t_min, int64_t_min));
    REQUIRE(cmp_less(int64_t_min + offset_int64_t, int32_t_min + offset_int32_t));
    REQUIRE_FALSE(cmp_less(int32_t_min + offset_int32_t, int64_t_min + offset_int64_t));
  }

  SUBCASE("left signed, right unsigned") {
    REQUIRE(cmp_less(-5, 3U));
    REQUIRE(cmp_less(3, 5U));
  }

  SUBCASE("left signed, right unsigned, different width") {
    REQUIRE(cmp_less(int32_t_max, uint64_t_max));
    REQUIRE_FALSE(cmp_less(int64_t_max, uint32_t_max));
    REQUIRE(cmp_less(int32_t_min, uint64_t_min));
    REQUIRE(cmp_less(int64_t_min, uint32_t_min));
    REQUIRE(cmp_less(int32_t_max - offset_int32_t, uint64_t_max));
    REQUIRE_FALSE(cmp_less(int64_t_max - offset_int64_t, uint32_t_max));
    REQUIRE(cmp_less(int32_t_min + offset_int32_t, uint64_t_min));
    REQUIRE(cmp_less(int64_t_min + offset_int64_t, uint32_t_min));
  }

  SUBCASE("left unsigned, right signed") {
    REQUIRE_FALSE(cmp_less(3U, -5));
    REQUIRE(cmp_less(3U, 5));
  }

  SUBCASE("left unsigned, right signed, different width") {
    REQUIRE(cmp_less(uint32_t_max, int64_t_max));
    REQUIRE_FALSE(cmp_less(uint64_t_max, int32_t_max));
    REQUIRE_FALSE(cmp_less(uint32_t_min, int64_t_min));
    REQUIRE_FALSE(cmp_less(uint64_t_min, int32_t_min));
    REQUIRE(cmp_less(uint32_t_max, int64_t_max - offset_int32_t));
    REQUIRE_FALSE(cmp_less(uint64_t_max, int32_t_max - offset_int64_t));
    REQUIRE_FALSE(cmp_less(uint32_t_min, int64_t_min + offset_int32_t));
    REQUIRE_FALSE(cmp_less(uint64_t_min, int32_t_min + offset_int64_t));
  }

  SUBCASE("bool, right") {
    REQUIRE(cmp_less(true, 5));
    REQUIRE(cmp_less(false, 1));
    REQUIRE_FALSE(cmp_less(false, -1));
  }

  SUBCASE("left, bool") {
    REQUIRE_FALSE(cmp_less(5, true));
    REQUIRE_FALSE(cmp_less(1, false));
    REQUIRE(cmp_less(-1, false));
  }
}
