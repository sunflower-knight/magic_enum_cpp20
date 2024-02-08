#pragma once

#include <array>
#include <string_view>

#include "magic_enum/core/core.hpp"
#include "magic_enum/core/enum_count.hpp"
#include "magic_enum/core/enum_name.hpp"

namespace magic_enum
{
    namespace detail
    {
        template <typename E, std::size_t... I>
        [[nodiscard]]
        constexpr auto entries_imp(std::index_sequence<I...>) noexcept
        {
            //todo 直接在names 和 values 调取数值
            constexpr auto entries = std::array<std::pair<E, std::string_view>, sizeof...(I)>{
                {{values_v<E>[I], enum_name_v<values_v<E>[I]>}...}
            };
            return entries;
        }
    }

    template <typename E>
    inline constexpr auto entries_v = detail::entries_imp<E>(std::make_index_sequence<enum_count<E>()>{});
    /**
     * @brief Returns `array<pair<E, string_view>, N>` with all pairs (value, name) where `N = number of enum values`, sorted by enum value.
     * @example auto color_entries = magic_enum::enum_entries<Color>();
     * color_entries -> {{Color::RED, "RED"}, {Color::BLUE, "BLUE"}, {Color::GREEN, "GREEN"}}
     */
    // Returns std::array  with pairs (value, name), sorted by enum value.
    template <Enum E>
    [[nodiscard]]
    consteval const auto& enum_entries() noexcept
    {
        using D = std::decay_t<E>;
        static_assert(is_reflected_v<D>, "magic_enum requires enum implementation and valid max and min.");
        //todo 放置在核心处
        return entries_v<D>;
    }
}
