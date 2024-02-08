#ifndef MAGIC_ENUM_CORE_ENUM_INDEX_HPP
#define MAGIC_ENUM_CORE_ENUM_INDEX_HPP

#include "magic_enum/core/concept.hpp"
#include "magic_enum/core/enum_count.hpp"

namespace magic_enum
{
    /**
     *  Obtains index in enum values from enum value.
     * `enum_index(value)` returns `optional<size_t>` with index.
     * @todo add assert runtime check
     */
    template <Enum E>
    [[nodiscard]] constexpr std::optional<std::size_t> enum_index(E value) noexcept {
        using D = Pure<E>;
        for(std::size_t i = 0; i < enum_count<D>(); ++i)
            if(values_v<D>[i] == value)
                return i;
        return std::nullopt; // Invalid value or out of range.
    }

    /**
     * @brief `enum_index<value>()` returns index.
     * If enum value does not have a index, occurs the compilation error `magic_enum::enum_index enum value does not have a index`.
     * @return index in enum values from static storage enum variable.
     */
    template <auto V>
    [[nodiscard]] consteval std::size_t enum_index() noexcept {
        using D = Pure<decltype(V)>;
        static_assert(Enum<D>, "support enum type");
        constexpr auto index_optional = enum_index<D>(V);
        static_assert(index_optional.has_value(), "magic_enum::enum_index enum value does not have a index.");
        return index_optional.value();
    }
}

#endif // MAGIC_ENUM_CORE_ENUM_INDEX_HPP
