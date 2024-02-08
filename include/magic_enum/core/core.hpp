#pragma once

#include "array"
#include "string_view"

#include "magic_enum/core/enum_config.hpp"
#include "magic_enum/core/enum_concept.hpp"

namespace magic_enum::detail
{
    template <auto V>
        requires Enum<decltype(V)>
    consteval auto enum_name_raw() noexcept
    {
        std::string_view name;
#if defined(_MSC_VER)
        name = __FUNCSIG__;
        //	ps: enum_name_raw<Person::ONE>(void)
        auto start = name.find("enum_name_raw<") + 14; // 6 is length of "enum_name_raw<"
        auto end = name.find_last_of('>');
#else //gcc + clang
        name = __PRETTY_FUNCTION__;
        //	ps: constexpr auto enum_name_raw() [with auto V = Person::ONE]
        auto start = name.find('[') + 15; // 8 is length of "[with auto V ="
        auto end = name.find_last_of(']');
#endif
        // 合法性检查
        if (name[start] == '(') //[with auto V = (<unnamed>::a_foo1::a_lt5)12] -> msvc+mingw
            return std::string_view{};
        // 是否特化了名字 -> todo 为了大多数使用不到的自定义字段名 增加编译时间 + 考虑移动到上层
        if constexpr (constexpr auto customize = customize::enum_name(V); customize.tag != customize::default_tag.tag)
        {
            static_assert(!customize.name.empty(), "customize name should not use empty string") ;
            return customize.name;
        }
        // 截取 enum value 的字段名
        auto pos = name.find_last_of(':');
        if (std::string_view::npos != pos && pos > start)
            start = pos + 1; //跳过':'
        //检查传入的 value 是否合法 -> value 可能不在 enum 的设定的数值中 -> 有数字不一定就是错误 ->
        //1. 字段名的中间有数字
        //2. 无效数字的转换
        //3. bool char 等其他类型转换过来的数据
        //4. 提前报错 -> 如果传入的不是enum
        //检查是否为合适的enum
        return name.substr(start, end - start);
    }

    /**
     * @brief 检查一个enum数值是否合法
     */
    template <auto V>
        requires Enum<decltype(V)>
    consteval bool valid_enum_value() noexcept
    {
        return enum_name_raw<V>().empty() ? false : true;
    }

    //计数+记录可用的数字有哪些 -> 杂糅了 记录的数据是其他用的
    //用户的工作 -> 传入的 rangeSize 检查大小 是否 >0 且在 UnderType 范围大小内
    //不同功能之间主要杂糅 -> 增加了编译时间
    //todo 检查offset +/- start 是否超出限制
    //unscope enum 编译器警告超出范围
    // 不合格的enum 数值 -> 返回空字符
    template <typename E, magic_underlying_type_t<E> V>
    consteval bool valid_number()
    {
        return valid_enum_value<static_cast<E>(V)>();
    }

    template <size_t Range>
    struct count_helper // NOLINT(*-pro-type-member-init)
    {
        size_t count = 0;
        bool valid[Range] = {false}; //todo 使用bitset 会不会更好
    };

    // check_valid<D,UnderType,MIN,RANGE_SIZE>();
    template <Enum E, typename UnderType, UnderType MIN, size_t RANGE_SIZE>
    consteval auto check_valid()
    {
        using D = Pure<E>;
        if constexpr (std::is_same_v<UnderType, bool>) //bool 特化
        {
            count_helper<2> ans; //因为不支持别名 布尔类型最多反射两个
            //valid[0] 为 false 元素 valid[1] 为true 元素
            if (valid_number<D, false>())
                ans.count++, ans.valid[0] = true;
            if (valid_number<D, true>())
                ans.count++, ans.valid[1] = true;
            return ans;
        }
        else
        {
            count_helper<RANGE_SIZE> ans;
            [&ans]<size_t... Nn>(std::index_sequence<Nn...>)
            {
                size_t index = 0;
                //todo size_t RangeSize 范围超过 int正数范围则不在程序控制中
                ans.count = ((valid_number<D, static_cast<int>(Nn) + MIN>()
                                  ? (ans.valid[index++] = true, 1)
                                  : (ans.valid[index++] = false, 0)) + ...);
            }(std::make_index_sequence<RANGE_SIZE>{});
            return ans;
        }
    }

    template <Enum E>
    consteval auto enum_count_imp() //todo 改名打表
    {
        using D = Pure<E>;
        using UnderType = magic_underlying_type_t<D>;
        //打表的范围设置
        constexpr UnderType MIN = detail::reflected_min_v<D>;
        constexpr UnderType MAX = detail::reflected_max_v<D>;
        static_assert(MAX > MIN, "use valid max and min");
        constexpr size_t RANGE_SIZE = MAX - MIN + 1; //左右闭合区间取范围 + 1
        constexpr count_helper helper = check_valid<D, UnderType, MIN, RANGE_SIZE>();
        constexpr size_t count = helper.count;
        std::array<D, count> values_v;
        //todo bool 处理
        for (size_t i = 0, j = 0; i < RANGE_SIZE; i++)
        {
            if (helper.valid[i] == true)
            {
                values_v[j] = static_cast<Pure<E>>(i + MIN);
                j++;
            }
        }
        return values_v;
    }
}

namespace magic_enum
{
    /**
    * @brief array<E, N> with all enum values (N = number of enum values) sorted by enum value.
    * @example magic_enum::enum_values<Color>() -> colors -> {Color::RED, Color::BLUE, Color::GREEN} -> colors[0] -> Color::RED
    */
    template <Enum E>
    constexpr auto values_v = detail::enum_count_imp<Pure<E>>();

    template <Enum E>
    constexpr bool is_reflected_v =
#ifndef  MAGIC_ENUM_NO_CHECK_REFLECTED_ENUM
        (values_v<E>.size() != 0);
#else
        true;
#endif
}
