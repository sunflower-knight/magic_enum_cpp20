#pragma once

#include "magic_enum/core/core.hpp"
#include "magic_enum/core/enum_integer.hpp"
#include "magic_enum/core/enum_count.hpp"
#include "magic_enum/core/enum_value.hpp"
#include "magic_enum/core/enum_name.hpp"

//* Obtains enum value from string or integer.
//* Returns `optional<E>`, using `has_value()` to check contains enum value and `value()` to get the enum value.
namespace magic_enum
{
    /**
     * @brief Obtains enum value from integer value
     * @return If argument is not enum's reflected and valid element's value, returns empty `optional`.
     * @example auto color = magic_enum::enum_cast<Color>(2);if (color.has_value()) {color.value() -> Color::RED}
     * @todo warning for narrow input value
     */
    template <typename E>
    [[nodiscard]]
    constexpr std::optional<Pure<E>> enum_cast(underlying_type_t<E> value) noexcept
    {
        using D = Pure<E>;
        static_assert(is_reflected_v<D>, "magic_enum requires enum implementation and valid max and min.");
        for (const auto& it : values_v<D>)
        {
            if (value == enum_integer(it))
                return it;
        }
        return {}; // Invalid value or out of range.
    }

    /**
     * @brief Obtains enum value from name -> runtime
     * @example auto color = magic_enum::enum_cast<Color>("GREEN"); if (color.has_value()) { color.value() -> Color::GREEN}
     */
    template <Enum E>
    [[nodiscard]]
    constexpr std::optional<Pure<E>> enum_cast(std::string_view name) noexcept
    {
        using D = Pure<E>;
        static_assert(is_reflected_v<D>, "magic_enum requires enum implementation and valid max and min.");
        //todo 这个检查可以放置在 core 里面
        for (std::size_t i = 0; i < enum_count<D>(); ++i)
        {
            if (name == enum_names<D>()[i])
                return enum_value<D>(i);
        }
        return std::nullopt; // Invalid value or out of range.
    }

    // todo 字符串比较转换
    //template<typename E, typename BinaryPredicate>
    //constexpr std::optional<E> enum_cast(std::string_view value, BinaryPredicate p) noexcept(is_nothrow_invocable_v	< BinaryPredicate > );
}
