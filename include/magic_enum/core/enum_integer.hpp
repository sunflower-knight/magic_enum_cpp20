#pragma once

#include "magic_enum/core/enum_concept.hpp"

namespace magic_enum
{
    // todo 未来实现别名警告
    // todo 如果之前有前后的映射 可以考虑使用编译期的数组数据 减少编译时间?
    // 是否需要检查
    //todo static_cast<UnderType<E>>(e_value) -> 检查原始是否在范围内
    // alias for to_underlying -> compatible magic_enum
    // template function alias with template para 推断
    // todo 提供编译期接口 -> 确保传入的 e_value 是可用的正常的
    // 变量引用减少 占据的字节
    /**
     * @brief Returns integer value from enum value. -> runtime and compile time
     * @example Color color = Color::RED; auto color_integer = magic_enum::enum_integer(color);
     * @note 不会检查 e_value 合法性 -> 例如是其他无效数字转换成 enum
     * @note 不受反射取值范围影响 -> 通用接口
     */
    template <typename E>
    constexpr auto enum_integer(E e_value) noexcept
    {
        return static_cast<magic_underlying_type_t<E>>(e_value);
    };

    template <typename E>
    constexpr auto to_underlying(E e_value) noexcept
    {
        return enum_integer<E>(e_value);
    };

    template <typename E>
    constexpr auto enum_underlying(E e_value) noexcept
    {
        return enum_integer<E>(e_value);
    }
}
