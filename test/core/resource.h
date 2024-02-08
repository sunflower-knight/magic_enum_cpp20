#pragma once

#define MAGIC_ENUM_NO_CHECK_REFLECTED_ENUM //todo 这是干嘛的
#define MAGIC_ENUM_RANGE_MIN (-120)
#define MAGIC_ENUM_RANGE_MAX 120

#include "magic_enum/core/check.hpp"
#include "magic_enum/core/enum_config.hpp"
#include "magic_enum/core/enum_customize.h"

#include "cinttypes"

static_assert(is_magic_enum_supported, "magic_enum: Unsupported compiler (https://github.com/Neargye/magic_enum#compiler-compatibility).");

enum class Color { RED = -12, GREEN = 7, BLUE = 15 };

template <>
consteval magic_enum::customize::customize_t magic_enum::customize::enum_name<Color>(Color value) noexcept {
    switch (value) {
    case Color::RED:
        return "red";
    default:
        return default_tag;
    }
}

enum class Numbers : int { one = 1, two, three, many = 127 };

enum Directions { Up = 85, Down = -42, Right = 120, Left = -120 };

enum number : unsigned long {
    one = 100,
    two = 200,
    three = 300,
    four = 400,
  #if defined(MAGIC_ENUM_SUPPORTED_ALIASES)
    _1 = one,
    _2 = two,
    _3 = three,
    _4 = four
  #endif
  };
template <>
struct magic_enum::customize::enum_range<number> {
    static constexpr int min = 100;
    static constexpr int max = 300;
};

enum class crc_hack {
    b5a7b602ab754d7ab30fb42c4fb28d82
  };

enum class crc_hack_2 {
    b5a7b602ab754d7ab30fb42c4fb28d82,
    d19f2e9e82d14b96be4fa12b8a27ee9f
  };

enum class MaxUsedAsInvalid : std::uint8_t {
    ONE,
    TWO = 63,
    INVALID = std::numeric_limits<std::uint8_t>::max()
  };
template <>
struct magic_enum::customize::enum_range<MaxUsedAsInvalid> {
    static constexpr int min = 0;
    static constexpr int max = 64;
};

enum class Binary : bool {
    ONE,
    TWO
  };
template <>
struct magic_enum::customize::enum_range<Binary> {
    static constexpr int min = 0;
    static constexpr int max = 64;
};

enum class BoolTest : bool { Yay, Nay };


enum lt1 { s1, loooooooooooooooooooong1 };
enum lt2 : unsigned { s2, loooooooooooooooooooong2 };
enum class lt3 { s3, loooooooooooooooooooong3 };
enum class lt4 : unsigned { s4, loooooooooooooooooooong4 };
class foo1 {
public:
    enum class lt5 { s5, loooooooooooooooooooong5 };
};
class foo2 {
public:
    enum lt6 { s6, loooooooooooooooooooong6 };
};

namespace boo1 {
    enum lt1 { s1, loooooooooooooooooooong1 };
    enum lt2 : unsigned { s2, loooooooooooooooooooong2 };
    enum class lt3 { s3, loooooooooooooooooooong3 };
    enum class lt4 : unsigned { s4, loooooooooooooooooooong4 };
    class foo1 {
    public:
        enum class lt5 { s5, loooooooooooooooooooong5 };
    };
    class foo2 {
    public:
        enum lt6 { s6, loooooooooooooooooooong6 };
    };
} // namespace boo1

namespace boo2 {
    namespace boo3 {
        enum lt1 { s1, loooooooooooooooooooong1 };
        enum lt2 : unsigned { s2, loooooooooooooooooooong2 };
        enum class lt3 { s3, loooooooooooooooooooong3 };
        enum class lt4 : unsigned { s4, loooooooooooooooooooong4 };
        class foo1 {
        public:
            enum class lt5 { s5, loooooooooooooooooooong5 };
        };
        class foo2 {
        public:
            enum lt6 { s6, loooooooooooooooooooong6 };
        };
    } // namespace boo2::boo3
} // namespace boo2

namespace {
    enum a_lt1 { s1, loooooooooooooooooooong1 };
    enum a_lt2 : unsigned { s2, loooooooooooooooooooong2 };
    enum class a_lt3 { s3, loooooooooooooooooooong3 };
    enum class a_lt4 : unsigned { s4, loooooooooooooooooooong4 };
    class a_foo1 {
    public:
        enum class a_lt5 { s5, loooooooooooooooooooong5 };
    };
    class a_foo2 {
    public:
        enum a_lt6 { s6, loooooooooooooooooooong6 };
    };
} // namespace

enum class LargeNumbers {
    First = -1024,
    Second = 1024
};
