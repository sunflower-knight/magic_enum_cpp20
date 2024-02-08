#pragma once

#include <string_view>

#include "magic_enum/core/enum_concept.hpp"
#include "magic_enum/core/enum_customize.h"

namespace magic_enum
{
    namespace detail
    {
        /**
         * @return <enum TestSpace::TestClass::Love> -> Love
         */
        template <typename E>
        consteval auto enum_type_name_imp() noexcept
        {
            //todo make start and end a another constexpr value to speed up compile time
            std::string_view name;
#ifdef _MSC_VER
            name = __FUNCSIG__; //	<enum TestSpace::TestClass::Love>
            auto start = name.find("<enum ") + 6; // 6 is length of "<enum "
            auto end = name.find_last_of('>');
#else //gcc + clang
            name = __PRETTY_FUNCTION__; // consteval auto raw_name() [with E = TestClass::Food]
            auto start = name.find('[') + 10; // 10 is length of "[with E = "
            auto end = name.find_last_of(']');
#endif
            auto pos = name.find_last_of(':');
            if (std::string_view::npos != pos && pos > start)
            {
                start = pos + 1; //跳过':'
            }
            return name.substr(start, end - start);
        }
    }

    /**
     * @brief Returns type name of enum as `string_view` null-terminated string.
     * @example auto color = Color::RED; auto type_name = magic_enum::enum_type_name<decltype(color)>(); -> type_name -> "Color"
     * @todo [feature] 输出 enum 类型的同时输出限定符
     */
    template <Enum E>
    consteval auto enum_type_name()
    {
        //customize
        if constexpr (auto constexpr type = customize::enum_type_name<Pure<E>>(); type.tag != customize::default_tag.
            tag)
        {
            static_assert(!type.name.empty(), "magic_enum::customize requires not empty string.");
            return type.name;
        }
        return detail::enum_type_name_imp<Pure<E>>(); //defalut
    }
}
