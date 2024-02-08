#ifndef MAGIC_ENUM_CORE_CORE_HPP
#define MAGIC_ENUM_CORE_CORE_HPP

#include "magic_enum/core/check.hpp"
#include "magic_enum/core/config.hpp"
#include "magic_enum/core/concept.hpp"

#include "magic_enum/core/enum_customize.hpp"
#include "magic_enum/core/enum_name.hpp"

namespace magic_enum::detail
{
    template <auto V>
    consteval bool valid_enum_value() noexcept {
        return enum_name_cus<decltype(V),V>().empty() ? false : true;
    }

    template <Enum E, magic_underlying_type_t<E> V>
    consteval bool valid_number() {
        return valid_enum_value<static_cast<E>(V)>();
    }

    template <size_t Range>
    struct count_helper{
        size_t count = 0;
        bool valid[Range] = {false}; //todo 使用bitset 会不会更好
    };

    // check_valid<D,UnderType,MIN,RANGE_SIZE>();
    template <Enum E, typename UnderType, UnderType MIN, size_t RANGE_SIZE>
    consteval auto check_valid() {
        using D = Pure<E>;
        if constexpr(std::is_same_v<UnderType,bool>) { //bool 特化
            count_helper<2> ans;                       //因为不支持别名 布尔类型最多反射两个
            //valid[0] 为 false 元素 valid[1] 为true 元素
            if(valid_number<D,false>())
                ans.count++, ans.valid[0] = true;
            if(valid_number<D,true>())
                ans.count++, ans.valid[1] = true;
            return ans;
        }
        else {
            count_helper<RANGE_SIZE> ans;
            [&ans]<size_t... Nn>(std::index_sequence<Nn...>){
                size_t index = 0;
                ans.count = ((valid_number<D,static_cast<int>(Nn) + MIN>()
                                  ? (ans.valid[index++] = true, 1)
                                  : (ans.valid[index++] = false, 0)) + ...);
            }(std::make_index_sequence<RANGE_SIZE>{ });
            return ans;
        }
    }

    template <Enum E>
    consteval auto enum_count_imp() //todo 改名打表
    {
        using D = Pure<E>;
        using UnderType = magic_underlying_type_t<D>;
        //打表的范围设置
        constexpr UnderType MIN = detail::reflected_min<D>();
        constexpr UnderType MAX = detail::reflected_max<D>();
        static_assert(MAX > MIN, "use valid max and min");
        constexpr size_t RANGE_SIZE = MAX - MIN + 1; //左右闭合区间取范围 + 1
        constexpr count_helper helper = check_valid<D,UnderType,MIN,RANGE_SIZE>();
        constexpr size_t count = helper.count;
        std::array<D,count> values_v;
        static_assert(count > 0 , "magic_enum requires enum implementation and valid max and min.");
        for(size_t i = 0, j = 0; i < RANGE_SIZE; i++) {
            if(helper.valid[i] == true) {
                values_v[j++] = static_cast<Pure<E>>(i + MIN);
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
    #ifdef  MAGIC_ENUM_NO_CHECK_REFLECTED_ENUM
    constexpr bool is_reflected_v = true;
    #else
    constexpr bool is_reflected_v = (values_v<E>.size() != 0);
    #endif
    template <typename E> //todo use sparase to make code faster in runtime
    constexpr bool is_sparse() noexcept {
        using U = magic_underlying_type_t<E>;
        if constexpr(std::is_same_v<U,bool>) {
            return false;// bool special case
        }
        else {
            constexpr auto min_v = (values_v<E>.size() > 0) ? static_cast<U>(values_v<E>.front()) : U{0};
            constexpr auto max_v = (values_v<E>.size() > 0) ? static_cast<U>(values_v<E>.back()) : U{0};
            return (max_v - min_v + 1) != values_v<E>.size(); /*(max_v - min_v + 1) is RangeSzie != reflected RangeSize*/
        }
    }

    template <typename E>
    constexpr bool is_sparse_v = is_sparse<Pure<E>>();
}

#endif
