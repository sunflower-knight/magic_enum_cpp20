#ifndef MAGIC_ENUM_CORE_ENUM_VALUE_HPP
#define MAGIC_ENUM_CORE_ENUM_VALUE_HPP

#include "magic_enum/core/concept.hpp"
#include "magic_enum/core/core.hpp"
#include "magic_enum/core/enum_count.hpp"

namespace magic_enum
{
    /**
     * @brief Return enum value at specified index. -> run or compile time
     * @note `enum_value(value)` no bounds checking is performed: the behavior is undefined if `index >= number of enum values`.
     * @todo  use assert in runtime interface
     * @example Color color = magic_enum::enum_value<Color>(1); -> Color::BLUE
     */
    template <Enum E>
    [[nodiscard]] constexpr auto enum_value(std::size_t index) noexcept {
        return values_v<Pure<E>>[index];
    }

    /**
     * @brief Returns enum value at specified index. -> compile time
     * @example Color color = magic_enum::enum_value<Color, 1>(); -> Color::BLUE
     * @note check if `Index >= number of enum values`
     */
    template <Enum E, std::size_t Index>
    [[nodiscard]] consteval auto enum_value() noexcept {
        using D = Pure<E>;
        static_assert(Index < enum_count<D>(), "magic_enum::enum_value out of range.");
        return enum_value<D>(Index);
    }

    /**
    * @return const array<E, N>& with all enum values (N = number of enum values) sorted by enum value.
    * @example magic_enum::enum_values<Color>() -> colors = {Color::RED, Color::BLUE, Color::GREEN} -> colors[0] == Color::RED
    */
    template <Enum E>
    [[nodiscard]] consteval const auto& enum_values() noexcept {
        return values_v<Pure<E>>;
    }
}

#endif // MAGIC_ENUM_CORE_ENUM_VALUE_HPP
