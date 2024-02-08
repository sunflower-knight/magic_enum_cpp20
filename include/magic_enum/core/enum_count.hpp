#pragma once

#include "magic_enum/core/core.hpp"

namespace magic_enum
{
    /**
     * @example constexpr auto color_count = magic_enum::enum_count<Color>(); // color_count -> 3
     * @return number of enum's reflected and valid elements.
     */
    template <Enum E>
    consteval size_t enum_count() noexcept {
        return values_v<Pure<E>>.size();
    }
}
