#pragma once

#include "string_view"

#include "magic_enum/core/enum_concept.hpp"
#include "magic_enum/core/core.hpp"
#include "magic_enum/core/enum_index.hpp"
#include "limits" //todo delete it ,  for debug use

namespace magic_enum
{
    /**
     * @note This version is compile faster on the compile time.
     * @note This version is not restricted to the enum_range limitation.
     * @note This version static_assert for not valid enum value.
     * @todo 传入的value的cvr是否会影响结果 -> 可能退化了
     * @return name from static storage enum variable.
     */
    template <auto V>
        requires Enum<decltype(V)>
    [[nodiscard]]
    constexpr std::string_view enum_name() noexcept
    {
        constexpr std::string_view name = detail::enum_name_raw<V>();
        static_assert(!name.empty(), "magic_enum::enum_name enum value does not have a name.");
        return name;
    }

    template <auto V>
        requires Enum<decltype(V)>
    inline constexpr auto enum_name_v = detail::enum_name_raw<V>();

    namespace detail
    {
        template <typename E, std::size_t... I>
        consteval auto names_imp(std::index_sequence<I...>) noexcept
        {
            return std::array<std::string_view, sizeof...(I)>{{enum_name<values_v<E>[I]>()...}};
        }

        template <Enum E>
        constexpr auto names_v = detail::names_imp<Pure<E>>(std::make_index_sequence<values_v<E>.size()>{}); //use count
    }

    /**
     * @brief compile and runtime support
     * @example Color color = Color::RED; auto color_name = magic_enum::enum_name(color); -> color_name -> "RED"
     * @return name from enum value.If enum value does not have name or value out of range, returns empty string.
     */
    template <Enum E>
    [[nodiscard]]
    constexpr std::string_view enum_name(E value) noexcept
    {
        using D = Pure<E>;
        static_assert(is_reflected_v<D>, "magic_enum requires enum implementation and valid max and min.");
        if (std::optional<size_t> index = enum_index<D>(value); index.has_value())
        {
            return detail::names_v<D>[index.value()];
        }
        return {};
    }

    /**
     * @return [const+reference] array<string_view, N> with all enum's reflected element's names sorted by enum value.
     * @example constexpr auto color_names = magic_enum::enum_names<Color>(); color_names -> {"RED", "BLUE", "GREEN"} color_names[0] -> "RED"
     * @return  array<string_view,N>
     */
    template <Enum E>
    consteval const auto& enum_names() noexcept
    {
        using D = Pure<E>;
        return detail::names_v<D>;
    }
}
