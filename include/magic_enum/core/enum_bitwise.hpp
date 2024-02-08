#ifndef MAGIC_ENUM_CORE_ENUM_BITWISE_HPP
#define MAGIC_ENUM_CORE_ENUM_BITWISE_HPP

#include "magic_enum/core/concept.hpp"

namespace magic_enum::bitwise_operators
{
    template <Enum E>
    constexpr E operator~(E rhs) noexcept {
        return static_cast<E>(~static_cast<underlying_type_t<E>>(rhs));
    }

    template <Enum E>
    constexpr E operator|(E lhs, E rhs) noexcept {
        return static_cast<E>(static_cast<underlying_type_t<E>>(lhs) | static_cast<underlying_type_t<E>>(rhs));
    }

    template <Enum E>
    constexpr E operator&(E lhs, E rhs) noexcept {
        return static_cast<E>(static_cast<underlying_type_t<E>>(lhs) & static_cast<underlying_type_t<E>>(rhs));
    }

    template <Enum E>
    constexpr E operator^(E lhs, E rhs) noexcept {
        return static_cast<E>(static_cast<underlying_type_t<E>>(lhs) ^ static_cast<underlying_type_t<E>>(rhs));
    }

    template <Enum E>
    constexpr E& operator|=(E& lhs, E rhs) noexcept {
        return lhs = (lhs | rhs);
    }

    template <Enum E>
    constexpr E& operator&=(E& lhs, E rhs) noexcept {
        return lhs = (lhs & rhs);
    }

    template <Enum E>
    constexpr E& operator^=(E& lhs, E rhs) noexcept {
        return lhs = (lhs ^ rhs);
    }
} // namespace magic_enum::bitwise_operators

#endif
