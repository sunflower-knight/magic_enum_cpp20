#pragma once

#include "magic_enum/core/enum_concept.hpp"
#include "magic_enum/core/enum_cast.hpp"

namespace magic_enum
{
    /**
    * @brief Checks whether enum contains value with such value.
    */
    template <Enum E>
    [[nodiscard]]
    constexpr bool enum_contains(E value) noexcept
    {
        using D = Pure<E>;
        using U = magic_underlying_type_t<D>;
        return static_cast<bool>(enum_cast<D>(static_cast<U>(value)));
    }

    /**
     * @brief  Checks whether enum contains value with such integer value.
     * @example enum_contains<Color>(2); -> true ; enum_contains<Color>(123); -> false
     * @todo 根据错误返回: 传入的数据不在 enum 中 ? 超出了反射的范围 ? 用户输入的编译报错传入的int类型数据超过了底层类型 ;
     */
    template <Enum E>
    constexpr bool enum_contains(magic_underlying_type_t<E> value) noexcept
    {
        using D = Pure<E>;
        return static_cast<bool>(enum_cast<D>(value)); //enum_cast -> optional
    }

    /**
     * @brief Checks whether enum contains enumerator with such name.
     * @example magic_enum::enum_contains<Color>("GREEN"); // -> true
     */
    template <Enum E>
    [[nodiscard]]
    constexpr bool enum_contains(std::string_view value) noexcept
    {
        using D = Pure<E>;
        return static_cast<bool>(enum_cast<D>(value)); //enum_cast -> optional
    }

    //magic_enum::enum_contains<Color>("fda"); // -> false
    //接受一个二元函数 作为比较 -> 例如小写和大写字母的enum 搜索时是等效的
    //template <typename E, typename BinaryPredicate>
    //constexpr bool enum_contains(std::string_view value, BinaryPredicate p) noexcept(is_nothrow_invocable_v<BinaryPredicate>);
}
