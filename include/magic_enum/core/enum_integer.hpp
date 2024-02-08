#ifndef MAGIC_ENUM_CORE_INTEGER_HPP
#define MAGIC_ENUM_CORE_INTEGER_HPP

#include "magic_enum/core/concept.hpp"

namespace magic_enum
{
    /**
     * @brief Returns integer value from enum value. -> runtime and compile time;
     * @example Color color = Color::RED; auto color_integer = magic_enum::enum_integer(color);
     * @note don't check whether the value is legal ; not restricted to the enum_range limitation
     */
    template <Enum E>
    [[nodiscard]] constexpr auto enum_integer(E e_value) noexcept {
        return static_cast<magic_underlying_type_t<E>>(e_value);
    };

    template <Enum E>
    [[nodiscard]] constexpr auto to_underlying(E e_value) noexcept {
        return static_cast<magic_underlying_type_t<E>>(e_value);
    };

    template <Enum E>
    [[nodiscard]] constexpr auto enum_underlying(E e_value) noexcept {
        return static_cast<magic_underlying_type_t<E>>(e_value);
    }
}

#endif // MAGIC_ENUM_CORE_INTEGER_HPP
