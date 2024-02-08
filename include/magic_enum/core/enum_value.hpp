#pragma once

#include "magic_enum/core/enum_concept.hpp"
#include "magic_enum/core/core.hpp"
#include "magic_enum/core/enum_count.hpp"

namespace magic_enum
{
    /**
     * @brief Return enum value at specified index. -> run or compile time
     * @note `enum_value(value)` no bounds checking is performed: the behavior is undefined if `index >= number of enum values`.
     * @note  用户自行确保输入的index 是安全的
     * @example Color color = magic_enum::enum_value<Color>(1); -> Color::BLUE
     */
    template <Enum E>
    constexpr auto enum_value(std::size_t index) noexcept //todo usr array::at with except
    {
        //todo 边界检查 -> 检测 -> 编译期执行 -> 不使用 array 自带检查
        using D = Pure<E>;
        static_assert(is_reflected_v<D>, "magic_enum requires enum implementation and valid max and min.");
        return values_v<D>[index];
    }

    /**
     * @brief Returns enum value at specified index. -> compile time
     * @example Color color = magic_enum::enum_value<Color, 1>(); -> Color::BLUE
     * @note `enum_value<Enum , Index >()` check if `Index >= number of enum values`, occurs the compilation error `magic_enum::enum_value out of range`.
     * @return
     */
    template <Enum E, std::size_t Index>
    consteval auto enum_value() noexcept
    {
        using D = Pure<E>;
        static_assert(is_reflected_v<D>, "magic_enum requires enum implementation and valid max and min.");
        static_assert(Index < enum_count<D>(), "magic_enum::enum_value out of range.");
        return enum_value<D>(Index);
    }

    /**
    * @return Returns const array<E, N>& with all enum values (N = number of enum values) sorted by enum value.
    * @example magic_enum::enum_values<Color>() -> colors = {Color::RED, Color::BLUE, Color::GREEN} -> colors[0] == Color::RED
    */
    template <Enum E>
    consteval const auto& enum_values() noexcept
    {
        return values_v<Pure<E>>;
    }
}
