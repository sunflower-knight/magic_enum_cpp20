#pragma once

#include <string_view>
#include <string>

#include  "magic_enum/core/enum_concept.hpp"

namespace magic_enum
{
    //todo 这段检查看不懂 可以放置在其他地方
    using char_type = std::string_view::value_type;
    static_assert(std::is_same_v<std::string_view::value_type, std::string::value_type>,
                  "magic_enum::customize requires same string_view::value_type and string::value_type");
    static_assert([]
    {
        if constexpr (std::is_same_v<char_type, wchar_t>)
        {
            constexpr const char c[] = "abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789|";
            constexpr const wchar_t wc[] = L"abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789|";
            static_assert(std::size(c) == std::size(wc),
                          "magic_enum::customize identifier characters are multichars in wchar_t.");

            for (std::size_t i = 0; i < std::size(c); ++i)
            {
                if (c[i] != wc[i])
                {
                    return false;
                }
            }
        }
        return true;
    }(), "magic_enum::customize wchar_t is not compatible with ASCII.");
}

namespace magic_enum::customize
{
    namespace detail
    {
        enum class customize_tag_better : bool
        {
            custom_tag = true,
            default_tag = false
        };

        enum class customize_tag
        {
            default_tag,
            invalid_tag,
            custom_tag //用户不可见
        };
    } // namespace magic_enum::customize::detail

    //每一个enum 都有一个属性 -> tag 和 stringview
    //type 可以拥有 , value 可以拥有 //todo 减少这个struct 空间占用大小
    struct customize_t
    {
        detail::customize_tag tag = detail::customize_tag::default_tag;
        std::string_view name; //empty

        constexpr customize_t(const std::string_view srt): tag(detail::customize_tag::custom_tag), name(srt)
        {
            // static_assert(!srt.empty(), "customize name should not be empty"); //todo
        }

        constexpr customize_t(const char_type* srt) : customize_t{std::string_view{srt}}
        {
        } //委托构造
        constexpr customize_t(const detail::customize_tag tag) : tag(tag)
        {
            // static_assert(tag != detail::customize_tag::custom_tag, "create custom_tag with string"); //todo 提供警告
        }
    };

    // Default customize. //todo 仅仅有返回自定义的结构体才需要被 特化出 name 字段
    inline constexpr customize_t default_tag = customize_t{detail::customize_tag::default_tag};

    // If need custom type name for enum, add specialization enum_type_name for necessary enum type.
    // @note don't use invalid tag here
    template <Enum E>
    consteval customize_t enum_type_name() noexcept
    {
        return default_tag;
    }

    // Invalid customize.
    inline constexpr customize_t invalid_tag = customize_t{detail::customize_tag::invalid_tag};

    // If need custom names for enum, add specialization enum_name for necessary enum type.
    template <Enum E>
    consteval customize_t enum_name(E value) noexcept
    {
        return default_tag; //todo 舍弃 customize 的结构体架构 ->
    }
} // namespace magic_enum::customize
