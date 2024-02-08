#pragma once
#include <type_traits>

namespace magic_enum
{
    // readability Alias -> 替代 sizeof<T> == 0 (即 concept或if constexpr 中的static assert布尔条件 可读性高)
    template <typename... T>
    inline constexpr bool always_false_v = false;

    // readability Alias
    template <typename E>
    using Pure = std::remove_cvref_t<E>;

    // Enum
    template <typename E>
    concept Enum = std::is_enum_v<Pure<E>>;

    // UnscopedEnum
    template <typename E>
    concept UnscopedEnum = Enum<E> && std::is_convertible_v<Pure<E>, std::underlying_type_t<Pure<E>>>;

    template <typename T> //  alias ->  兼容magic_enum
    struct is_unscoped_enum : std::bool_constant<UnscopedEnum<T>>
    {
    };

    template <typename T> // Helper variable template.
    constexpr bool is_unscoped_enum_v = UnscopedEnum<T>;

    // ScopedEnum
    template <typename E>
    concept ScopedEnum = Enum<E> && !UnscopedEnum<E>;

    template <typename E> //  alias -> magic_enum
    struct is_scoped_enum : std::bool_constant<ScopedEnum<E>>
    {
    };

    template <typename T> // Helper variable template.
    constexpr bool is_scoped_enum_v = ScopedEnum<T>;

    // If T is a complete enumeration type, provides a member typedef type that names the underlying type of T.
    // Otherwise, if T is not an enumeration type, there is no member type. Otherwise (T is an incomplete enumeration type), the program is ill-formed.
    template <Enum E>
    using magic_underlying_type_t = std::underlying_type_t<Pure<E>>;

    template <Enum T> //  alias -> magic_enum
    struct underlying_type
    {
        using type = magic_underlying_type_t<T>;
    };

    template <Enum T> // Helper variable template.
    using underlying_type_t = underlying_type<T>::type;
}
