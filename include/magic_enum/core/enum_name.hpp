#ifndef MAGIC_ENUM_CORE_NAME_HPP
#define MAGIC_ENUM_CORE_NAME_HPP

#include "magic_enum/core/concept.hpp"

namespace magic_enum
{
    namespace detail
    {
        struct str_view{
            const char* str_ = nullptr;
            std::size_t size_ = 0;
        };

        template <auto V>
        constexpr auto n() noexcept {
            #if defined(MAGIC_ENUM_GET_ENUM_NAME_BUILTIN)
            constexpr auto name_ptr = MAGIC_ENUM_GET_ENUM_NAME_BUILTIN(V);
            auto name = name_ptr ? str_view{name_ptr, std::char_traits<char>::length(name_ptr)} : str_view{};
            #elif defined(__clang__)
            str_view name;
            if constexpr(sizeof(__PRETTY_FUNCTION__) == sizeof(__FUNCTION__)) {
                static_assert(always_false_v<decltype(V)>, "magic_enum::detail::n requires __PRETTY_FUNCTION__.");
                return string_view{ };
            }
            else {
                name.size_ = sizeof(__PRETTY_FUNCTION__) - 36;
                name.str_ = __PRETTY_FUNCTION__ + 34;
            }
            if(name.size_ > 22 && name.str_[0] == '(' && name.str_[1] == 'a' && name.str_[10] == ' ' && name.str_[22] == ':') {
                name.size_ -= 23;
                name.str_ += 23;
            }
            if(name.str_[0] == '(' || name.str_[0] == '-' || (name.str_[0] >= '0' && name.str_[0] <= '9')) {
                name = str_view{ };
            }
            #elif defined(__GNUC__)
            auto name = str_view{__PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__) - 1};
            if constexpr (sizeof(__PRETTY_FUNCTION__) == sizeof(__FUNCTION__)) {
              static_assert(always_false_v<decltype(V)>, "magic_enum::detail::n requires __PRETTY_FUNCTION__.");
                return string_view{ };
            } else if (name.str_[name.size_ - 1] == ']') {
              name.size_ -= 55;
              name.str_ += 54;
            } else {
              name.size_ -= 40;
              name.str_ += 37;
            }
            if (name.str_[0] == '(') {
              name = str_view{};
            }
            #elif defined(_MSC_VER)
            str_view name;
            if((__FUNCSIG__[5] == '_' && __FUNCSIG__[35] != '(') || (__FUNCSIG__[5] == 'c' && __FUNCSIG__[41] != '(')) {
                // CLI/C++ workaround (see https://github.com/Neargye/magic_enum/issues/284).
                name.str_ = __FUNCSIG__;
                name.str_ += 35;
                name.size_ = sizeof(__FUNCSIG__) - 52;
            }
            #else
                auto name = str_view{};
            #endif
            std::size_t p = 0;
            for(std::size_t i = name.size_; i > 0; --i) {
                if(name.str_[i] == ':') {
                    p = i + 1;
                    break;
                }
            }
            if(p > 0) {
                name.size_ -= p;
                name.str_ += p;
            }
            return string_view(name.str_, name.size_);
        }

        template <Enum E , E V>
        consteval auto enum_name_cus() noexcept {
            constexpr auto custom = customize::enum_name<E>(V);
            static_assert(std::is_same_v<Pure<decltype(custom)>,customize::customize_t>,
                          "magic_enum::customize speciliztion requires customize_t type as return type.");
            if constexpr(custom.tag == customize::detail::customize_tag::custom_tag) {
                static_assert(!custom.name.empty(), "customize name should not use empty string") ;
                return custom.name;
            }
            else if(custom.tag == customize::detail::customize_tag::invalid_tag) {
                return std::string_view{ };
            }
            else {
                return detail::n<V>();
            }
        }

        template <typename E, E V>
        constexpr auto enum_name_v = enum_name_cus<E,V>();
    }

    /**
     * @brief
     * @note This version is compile faster + not restricted to the enum_range limitation + static_assert for not valid enum value.
     * @return name from static storage enum variable.
     */
    template <auto V>
    [[nodiscard]] consteval auto enum_name() noexcept {
        using D = Pure<decltype(V)>;
        static_assert(Enum<D>, "magic_enum::enum_name recept Enum value only");
        constexpr std::string_view name = detail::enum_name_v<D,V>;
        static_assert(!name.empty(), "magic_enum::enum_name enum value does not have a name.");
        return name;
    }
}

#endif // MAGIC_ENUM_CORE_NAME_HPP
