#ifndef MAGIC_ENUM_CORE_ENUM_CONTAINS_HPP
#define MAGIC_ENUM_CORE_ENUM_CONTAINS_HPP

#include "magic_enum/core/concept.hpp"
#include "magic_enum/core/enum_cast.hpp"

namespace magic_enum
{
    /**
    * @brief Checks whether enum contains such value.
    */
    template <Enum E>
    [[nodiscard]] constexpr bool enum_contains(E value) noexcept {
        using D = Pure<E>;
        using U = magic_underlying_type_t<D>;
        return static_cast<bool>(enum_cast<D>(static_cast<U>(value)));
    }

    /**
     * @brief  Checks whether enum contains value with such integer value.
     * @example enum_contains<Color>(2); -> true ; enum_contains<Color>(123); -> false
     */
    template <Enum E>
    [[nodiscard]] constexpr bool enum_contains(magic_underlying_type_t<E> value) noexcept {
        using D = Pure<E>;
        return static_cast<bool>(enum_cast<D>(value)); //enum_cast -> optional
    }

    /**
     * @brief Checks whether enum contains enumerator with such name.
     * @example magic_enum::enum_contains<Color>("GREEN"); // -> true
     */
    template <Enum E>
    [[nodiscard]] constexpr bool enum_contains(std::string_view value) noexcept {
        using D = Pure<E>;
        return static_cast<bool>(enum_cast<D>(value)); //enum_cast -> optional
    }
}

#endif // MAGIC_ENUM_CORE_ENUM_CONTAINS_HPP
