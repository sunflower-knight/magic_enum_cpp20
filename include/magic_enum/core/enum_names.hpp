#ifndef MAGIC_ENUM_CORE_NAMES_HPP
#define MAGIC_ENUM_CORE_NAMES_HPP

#include "magic_enum/core/concept.hpp"
#include "magic_enum/core/core.hpp"
#include "magic_enum/core/enum_name.hpp"
#include "magic_enum/core/enum_index.hpp"

namespace magic_enum
{
    namespace detail
    {
        template <typename E, std::size_t... I>
        consteval auto names_imp(std::index_sequence<I...>) noexcept {
            return std::array<std::string_view,sizeof...(I)>{{enum_name<values_v<E>[I]>()...}};
        }

        template <typename E>
        constexpr auto names_v = detail::names_imp<E>(std::make_index_sequence<values_v<E>.size()>{ }); //use count
    }

    /**
     * @example Color color = Color::RED; auto color_name = magic_enum::enum_name(color); -> color_name -> "RED"
     * @return name from enum value.If enum value is valid or value out of reflted range, returns empty string.
     */
    template <Enum E>
    [[nodiscard]] constexpr std::string_view enum_name(E value) noexcept {
        using D = Pure<E>;
        if(std::optional<size_t> index = enum_index<D>(value); index.has_value()) {
            return detail::names_v<D>[index.value()];
        }
        return { };
    }

    /**
     * @return [const+reference] array<string_view, N> with all enum's reflected element's names sorted by enum value.
     * @example auto color_names = magic_enum::enum_names<Color>(); color_names -> {"RED", "BLUE", "GREEN"} color_names[0] -> "RED"
     * @return  array<string_view,N>
     */
    template <Enum E>
    [[nodiscard]] consteval const auto& enum_names() noexcept {
        using D = Pure<E>;
        return detail::names_v<D>;
    }
}
#endif // MAGIC_ENUM_CORE_NAMES_HPP
