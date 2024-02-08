#ifndef MAGIC_ENUM_CORE_ENUM_CONCEPT_HPP
#define MAGIC_ENUM_CORE_ENUM_CONCEPT_HPP

#include <type_traits>

namespace magic_enum
{
    // readability Alias -> replace sizeof<T> == 0 as a alwayse false
    template <typename... T>
    inline constexpr bool always_false_v = false;

    // readability Alias
    template <typename T>
    using Pure = std::remove_cvref_t<T>;

    // Enum
    template <typename T>
    concept Enum = std::is_enum_v<Pure<T>>;

    // UnscopedEnum
    template <typename T>
    concept UnscopedEnum = Enum<T> && std::is_convertible_v<Pure<T>,std::underlying_type_t<Pure<T>>>;

    template <typename T>
    struct [[deprecated]] is_unscoped_enum : std::bool_constant<UnscopedEnum<T>>{ };

    template <typename T>
    constexpr bool is_unscoped_enum_v = UnscopedEnum<T>;

    // ScopedEnum
    template <typename T>
    concept ScopedEnum = Enum<T> && !UnscopedEnum<T>;

    template <typename T>
    struct   [[deprecated]] is_scoped_enum : std::bool_constant<ScopedEnum<T>>{ };

    template <typename T> // Helper variable template.
    constexpr bool is_scoped_enum_v = ScopedEnum<T>;

    // If T is a complete enumeration type, provides a member typedef type that names the underlying type of T.
    // Otherwise, if T is not an enumeration type, there is no member type. Otherwise (T is an incomplete enumeration type), the program is ill-formed.
    template <Enum T>
    using magic_underlying_type_t = std::underlying_type_t<Pure<T>>;

    template <Enum T>
    struct [[deprecated]] underlying_type{
        using type = magic_underlying_type_t<T>;
    };

    template <Enum T>
    using underlying_type_t [[deprecated]] = magic_underlying_type_t<T>;

    template <auto V,Enum T = Pure<decltype(V)>>
    using enum_constant = std::integral_constant<T,V>;
}

#endif // MAGIC_ENUM_CORE_ENUM_CONCEPT_HPP
