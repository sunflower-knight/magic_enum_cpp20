#pragma once

#include <type_traits>

#ifndef MAGIC_ENUM_USING_ALIAS_OPTIONAL
// #  include <optional>
#endif
#ifndef MAGIC_ENUM_USING_ALIAS_STRING
// #  include <string>
#endif
#ifndef MAGIC_ENUM_USING_ALIAS_STRING_VIEW
// #  include <string_view>
#endif

//assert for runtime
#ifdef MAGIC_ENUM_NO_ASSERT
#  define MAGIC_ENUM_ASSERT(...) static_cast<void>(0)
#elif !defined(MAGIC_ENUM_ASSERT)
#  include <cassert>
#  define MAGIC_ENUM_ASSERT(...) assert((__VA_ARGS__))
#endif

#include <limits> //number max
#include "magic_enum/core/enum_concept.hpp"

/**
 * @MAGIC_ENUM_RANGE_MIN Enum value must be greater or equals than MAGIC_ENUM_RANGE_MIN. By default, MAGIC_ENUM_RANGE_MIN = -128.
 * If need another min range for all enum types by default, redefine the macro MAGIC_ENUM_RANGE_MIN.
 * @MAGIC_ENUM_RANGE_MAX Enum value must be less or equals than MAGIC_ENUM_RANGE_MAX. By default, MAGIC_ENUM_RANGE_MAX = 128.
 * If need another max range for all enum types by default, redefine the macro MAGIC_ENUM_RANGE_MAX.
 * @note [MAGIC_ENUM_RANGE_MIN,MAGIC_ENUM_RANGE_MAX] 左右闭区间
 */
#ifndef MAGIC_ENUM_RANGE_MIN
#  define MAGIC_ENUM_RANGE_MIN (-128)
#endif
#ifndef MAGIC_ENUM_RANGE_MAX
#  define MAGIC_ENUM_RANGE_MAX 127
#endif

namespace magic_enum::customize
{
    /**
     * @brief 反射的值范围默认配置
     */
    template <Enum E>
    struct enum_range
    {
        using UnderType = magic_underlying_type_t<E>;
        static constexpr int min = MAGIC_ENUM_RANGE_MIN;
        //如果目标类型是正整数类型 则
        static constexpr int max = MAGIC_ENUM_RANGE_MAX;
        static_assert(max > min, "magic_enum::customize::enum_range requires max > min.");
    };
}

namespace magic_enum::detail
{
    template <typename L, typename R>
    constexpr bool cmp_less(L lhs, R rhs) noexcept
    {
        static_assert(std::is_integral_v<L> && std::is_integral_v<R>,
                      "magic_enum::detail::cmp_less requires integral type.");
        if constexpr (std::is_signed_v<L> == std::is_signed_v<R>)
        {
            // If same signedness (both signed or both unsigned).
            return lhs < rhs;
        }
        else if constexpr (std::is_same_v<L, bool>)
        {
            // bool special case
            return static_cast<R>(lhs) < rhs;
        }
        else if constexpr (std::is_same_v<R, bool>)
        {
            // bool special case
            return lhs < static_cast<L>(rhs);
        }
        else if constexpr (std::is_signed_v<R>)
        {
            // If 'right' is negative, then result is 'false', otherwise cast & compare.
            return rhs > 0 && lhs < static_cast<std::make_unsigned_t<R>>(rhs);
        }
        else
        {
            // If 'left' is negative, then result is 'true', otherwise cast & compare.
            return lhs < 0 || static_cast<std::make_unsigned_t<L>>(lhs) < rhs;
        }
    }

    /**
     * @brief 实际需要反射的最大值范围
     */
    template <Enum E>
    consteval auto reflected_min() noexcept
    {
        constexpr auto rhs = std::numeric_limits<magic_underlying_type_t<E>>::min(); // min 和 lowest 等效 在整数中
        constexpr auto lhs = customize::enum_range<E>::min; //int
        return detail::cmp_less(lhs, rhs) ? rhs : lhs; //
    }

    template <Enum E>
    consteval auto reflected_max() noexcept
    {
        constexpr auto rhs = std::numeric_limits<magic_underlying_type_t<E>>::max();
        constexpr auto lhs = customize::enum_range<E>::max; //不支持 bool 和 flag
        //todo 检查用户反射的类型是否为bool char 等 std::cmpless 不支持的类型
        return detail::cmp_less(lhs, rhs) ? lhs : rhs; //	static_assert(); //todo 检查类型是否相同
    }

    template <Enum E>
    constexpr auto reflected_min_v = reflected_min<E>();
    template <Enum E>
    constexpr auto reflected_max_v = reflected_max<E>();
}
