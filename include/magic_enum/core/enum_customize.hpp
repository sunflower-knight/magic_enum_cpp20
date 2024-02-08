#ifndef MAGIC_ENUM_CORE_ENUM_CUSTOMIZE_HPP
#define MAGIC_ENUM_CORE_ENUM_CUSTOMIZE_HPP

#include  "magic_enum/core/concept.hpp"
#include  "magic_enum/core/check.hpp"

namespace magic_enum::customize
{
    /**
     * @brief If need custom reflecte range for enum, add specialization enum_range for necessary enum type.
     */
    template <Enum E>
    struct enum_range{
        using UnderType = magic_underlying_type_t<E>;
        static constexpr int min = MAGIC_ENUM_RANGE_MIN;
        static constexpr int max = MAGIC_ENUM_RANGE_MAX;
        static_assert(max > min, "magic_enum::customize::enum_range requires max > min.");
    };
}

namespace magic_enum::detail
{
    /**@attention better than std::cmpless , support bool,char,int...*/
    template <typename L, typename R>
    consteval bool cmp_less(L lhs, R rhs) noexcept {
        static_assert(std::is_integral_v<L> && std::is_integral_v<R>, "magic_enum::detail::cmp_less requires integral type.");
        if constexpr(std::is_signed_v<L> == std::is_signed_v<R>)
            return lhs < rhs; // If same signedness (both signed or both unsigned).
        else if constexpr(std::is_same_v<L,bool>)
            return static_cast<R>(lhs) < rhs; // bool special case
        else if constexpr(std::is_same_v<R,bool>)
            return lhs < static_cast<L>(rhs); // bool special case
        else if constexpr(std::is_signed_v<R>)
            // If 'right' is negative, then result is 'false', otherwise cast & compare.
            return rhs > 0 && lhs < static_cast<std::make_unsigned_t<R>>(rhs);
        else
            // If 'left' is negative, then result is 'true', otherwise cast & compare.
            return lhs < 0 || static_cast<std::make_unsigned_t<L>>(lhs) < rhs;
    }

    /**@attention if user don't specialize max or min in customize , use default value by SFINAE */
    template <typename T, typename = void>
    constexpr int range_min = MAGIC_ENUM_RANGE_MIN;
    template <typename T>
    constexpr auto range_min<T,std::void_t<decltype(customize::enum_range<T>::min)>> = customize::enum_range<T>::min;
    template <typename T, typename = void>
    constexpr int range_max = MAGIC_ENUM_RANGE_MAX;
    template <typename T>
    constexpr auto range_max<T,std::void_t<decltype(customize::enum_range<T>::max)>> = customize::enum_range<T>::max;

    /**@note reflected max and min interger*/
    template <Enum E>
    consteval auto reflected_min() noexcept {
        constexpr auto rhs = std::numeric_limits<magic_underlying_type_t<E>>::min();
        constexpr auto lhs = range_min<E>;
        static_assert(std::is_integral_v<decltype(lhs)>, "magic_enum::detail requires integral type in enum_range specialization.");
        return detail::cmp_less(lhs, rhs) ? rhs : lhs;
    }

    template <Enum E>
    consteval auto reflected_max() noexcept {
        constexpr auto rhs = std::numeric_limits<magic_underlying_type_t<E>>::max();
        constexpr auto lhs = range_max<E>;
        static_assert(std::is_integral_v<decltype(lhs)>, "magic_enum::detail requires integral type in enum_range specialization.");
        return detail::cmp_less(lhs, rhs) ? lhs : rhs;
    }
}

namespace magic_enum::customize
{
    namespace detail
    {
        enum class customize_tag{
            default_tag,
            invalid_tag,
            custom_tag //用户不可见
        };
    } // namespace magic_enum::customize::detail

    struct customize_t{
        detail::customize_tag tag = detail::customize_tag::default_tag;
        std::string_view name; //empty
        constexpr customize_t(const std::string_view srt): tag(detail::customize_tag::custom_tag), name(srt) {
            // static_assert(!srt.empty(), "customize name should not be empty"); //todo
        }

        constexpr customize_t(const char_type* srt) : customize_t{std::string_view{srt}} { } //委托构造
        constexpr customize_t(const detail::customize_tag tag) : tag(tag) {
            // static_assert(tag != detail::customize_tag::custom_tag, "create custom_tag with string"); //todo 提供警告
        }
    };

    // Default customize.
    inline constexpr customize_t default_tag = customize_t{detail::customize_tag::default_tag};

    // Invalid customize.
    inline constexpr customize_t invalid_tag = customize_t{detail::customize_tag::invalid_tag};

    // If need custom type name for enum, add specialization enum_type_name for necessary enum type.
    /**@note don't use invalid tag here in specialization*/
    template <Enum E>
    consteval customize_t enum_type_name() noexcept {
        return default_tag; //todo  deprecated struct customize and type name don't support invalid tag
    }

    // If need custom names for enum, add specialization enum_name for necessary enum type.
    template <Enum E>
    consteval customize_t enum_name(E value) noexcept {
        return default_tag;
    }
} // namespace magic_enum::customize

#endif // MAGIC_ENUM_CORE_ENUM_CUSTOMIZE_HPP
