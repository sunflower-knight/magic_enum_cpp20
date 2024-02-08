#pragma once

#include <iosfwd>
#include <optional>

#include "magic_enum/magic_enum.hpp"
#include <istream>

namespace magic_enum::ostream_operators
{
	template<typename Char, typename Traits, Enum E>
	std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, E value)
	{
		using D = std::decay_t<E>;
		using U = magic_underlying_type_t<D>;
		if (const auto name = enum_name<D>(value); !name.empty())
		{
			for (const auto c : name)
			{
				os.put(c);
			}
			return os;
		}
		//todo 不支持的类型则报错
		return (os << static_cast<U>(value)); //如果不在反射的元素中 直接返回整数
	}

	template<typename Char, typename Traits, Enum E>
	std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, std::optional<E> value)
	{
		return value ? (os << *value) : os;
	}
}// namespace magic_enum::ostream_operators

namespace magic_enum::istream_operators
{
	template<typename Char, typename Traits, Enum E>
	std::basic_istream<Char, Traits>& operator>>(std::basic_istream<Char, Traits>& is, E& value)
	{
		using D = std::decay_t<E>;
		std::basic_string<Char, Traits> s;
		is >> s;
		if (const auto v = enum_cast<D>(s))
		{
			value = *v;
		}
		else
		{
			is.setstate(std::basic_ios<Char>::failbit);
		}
		return is;
	}
} // namespace magic_enum::istream_operators

namespace magic_enum::iostream_operators
{
	using magic_enum::ostream_operators::operator<<;
	using magic_enum::istream_operators::operator>>;
} // namespace magic_enum::iostream_operators

