#ifndef MAGIC_ENUM_CORE_ENUM_CAST_HPP
#define MAGIC_ENUM_CORE_ENUM_CAST_HPP

#include "magic_enum/core/core.hpp"
#include "magic_enum/core/enum_integer.hpp"
#include "magic_enum/core/enum_count.hpp"
#include "magic_enum/core/enum_value.hpp"
#include "magic_enum/core/enum_names.hpp"

namespace magic_enum
{
    /**
     * @brief Obtains enum value from integer value
     * @return If argument is not enum's reflected and valid element's value, returns empty `optional`.
     * @example auto color = magic_enum::enum_cast<Color>(2);if (color.has_value()) {color.value() -> Color::RED}
     */
    template <typename E>
    [[nodiscard]] constexpr std::optional<Pure<E>> enum_cast(magic_underlying_type_t<E> value) noexcept {
        using D = Pure<E>;
        for(const auto& it : values_v<D>)
            if(value == enum_integer(it))
                return it;
        return std::nullopt ; // Invalid value or out of range.
    }

    /**
     * @brief Obtains enum value from name -> runtime
     * @example auto color = magic_enum::enum_cast<Color>("GREEN"); if (color.has_value()) { color.value() -> Color::GREEN}
     */
    template <Enum E>
    [[nodiscard]] constexpr std::optional<Pure<E>> enum_cast(std::string_view name) noexcept {
        using D = Pure<E>;
        for(std::size_t i = 0; i < enum_count<D>(); ++i)
            if(name == enum_names<D>()[i])
                return enum_value<D>(i);
        return std::nullopt; // Invalid value or out of range.
    }
}

#endif // MAGIC_ENUM_CORE_ENUM_CAST_HPP
