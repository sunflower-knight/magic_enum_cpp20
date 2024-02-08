#ifndef MAGIC_ENUM_CORE_ENUM_TYPE_NAME_HPP
#define MAGIC_ENUM_CORE_ENUM_TYPE_NAME_HPP

#include "magic_enum/core/concept.hpp"
#include "magic_enum/core/enum_customize.hpp"

namespace magic_enum
{
    namespace detail
    {
        /**
         * @return <enum TestSpace::TestClass::Love> -> Love
         */
        template <typename E>
        consteval auto enum_type_name_imp() noexcept {
            //todo make start as constexpr value to speed up compile time
            std::string_view name;
            #if defined(MAGIC_ENUM_GET_TYPE_NAME_BUILTIN)
            name =  ;//todo support reshaper samrter
            #elif defined(__clang__)
            name = __PRETTY_FUNCTION__;           // consteval auto raw_name() [with E = TestClass::Food]
            auto start = name.find('[') + 5; // 10 is length of "[with E = "
            auto end = name.find_last_of(']');
            #elif defined(__GNUC__)
            name = __PRETTY_FUNCTION__;           // consteval auto raw_name() [with E = TestClass::Food]
            auto start = name.find('[') + 10; // 10 is length of "[with E = "
            auto end = name.find_last_of(']');
            #elif defined(_MSC_VER)
            name = __FUNCSIG__;                   //	<enum TestSpace::TestClass::Love>
            auto start = name.find("<enum ") + 6; // 6 is length of "<enum "
            auto end = name.find_last_of('>');
            #endif
            auto pos = name.find_last_of(':');
            if(std::string_view::npos != pos && pos > start) {
                start = pos + 1; //跳过':'
            }
            return name.substr(start, end - start);
        }

        /**@brief get customize or default enum_type_name */
        template <typename E>
        consteval std::string_view type_name() {
            //todo simplyize the design for customize and interface
            constexpr auto custom = customize::enum_type_name<E>();
            static_assert(std::is_same_v<Pure<decltype(custom)>,customize::customize_t>,
                          "magic_enum requires customize_t as return type for specialize customize::enum_type_name<>.");
            if constexpr(custom.tag == customize::detail::customize_tag::custom_tag) {
                static_assert(!custom.name.empty(), "magic_enum::customize requires not empty string.");
                return custom.name; //customize
            }
            else
                return detail::enum_type_name_imp<E>(); //defalut
        }

        template <typename E>
        constexpr auto type_name_v = detail::type_name<E>();
    }

    /**
     * @brief Returns type name of enum as `string_view` null-terminated string.
     * @example auto color = Color::RED; auto type_name = magic_enum::enum_type_name<decltype(color)>(); -> type_name -> "Color"
     * @todo [feature] return namespace::class::EnumTypeName as a option
     */
    template <Enum E>
    [[nodiscard]] constexpr std::string_view enum_type_name() noexcept {
        using D = Pure<E>;
        constexpr string_view name = detail::type_name_v<D>;
        static_assert(!name.empty(), "magic_enum::enum_type_name enum type does not have a name.");
        return name;
    }
}

#endif // MAGIC_ENUM_CORE_ ENUM_TYPE_NAME_HPP
