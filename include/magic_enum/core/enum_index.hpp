#pragma once

#include <optional>

#include "magic_enum/core/enum_concept.hpp"
#include "magic_enum/core/enum_count.hpp"
#include "magic_enum/core/enum_value.hpp"

namespace magic_enum
{
    /**
     *  Obtains index in enum values from enum value.
     * `enum_index(value)` returns `optional<size_t>` with index.
     */
    template <Enum E>
    constexpr std::optional<std::size_t> enum_index(E value) noexcept
    {
        // Obtains index in enum values from enum value.
        // Returns optional with index.
        using D = Pure<E>;
        static_assert(is_reflected_v<D>, "magic_enum requires enum implementation and valid max and min."); //todo 放在顶层
        // 计数 + 布尔数组记录
        for (std::size_t i = 0; i < enum_count<D>(); ++i)
        {
            if (values_v<D>[i] == value)
                return i;
        }
        return std::nullopt; // Invalid value or out of range.
    }

    /**
     * @brief `enum_index<value>()` returns index.
     * If enum value does not have a index, occurs the compilation error `magic_enum::enum_index enum value does not have a index`.
     * @return index in enum values from static storage enum variable.
     */
    template <auto V>
    [[nodiscard]]
    consteval std::size_t enum_index() noexcept
    {
        using D = Pure<decltype(V)>;
        static_assert(Enum<D>, "support enum type");
        static_assert(is_reflected_v<D>, "magic_enum requires enum implementation and valid max and min.");

        constexpr std::optional<std::size_t> index = enum_index<D>(V);
        static_assert(index.has_value(), "magic_enum::enum_index enum value does not have a index."); //错误的类型 或者 没有被反射到
        return *index;
    }
}
