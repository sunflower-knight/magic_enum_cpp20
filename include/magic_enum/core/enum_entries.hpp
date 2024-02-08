#pragma once

#include "magic_enum/core/core.hpp"
#include "magic_enum/core/enum_count.hpp"

namespace magic_enum
{
    namespace detail
    {
        template <typename E, std::size_t... I>
        constexpr auto entries_imp(std::index_sequence<I...>) noexcept {
            constexpr auto entries = std::array<std::pair<E,std::string_view>,sizeof...(I)>{
                    {{values_v<E>[I], enum_names<E>()[I]}...}
            };
            return entries;
        }

        template <typename E>
        constexpr auto entries_v = detail::entries_imp<E>(std::make_index_sequence<enum_count<E>()>{ });
    }

    /**
     * @brief Returns `array<pair<E, string_view>, N>` with all pairs (value, name) where `N = number of enum values`, sorted by enum value.
     * @example auto color_entries = magic_enum::enum_entries<Color>();
     * color_entries -> {{Color::RED, "RED"}, {Color::BLUE, "BLUE"}, {Color::GREEN, "GREEN"}}
     */
    // Returns std::array  with pairs (value, name), sorted by enum value.
    template <Enum E>
    [[nodiscard]] consteval const auto& enum_entries() noexcept {
        return detail::entries_v<Pure<E>>;
    }
}
