//  __  __             _        ______                          _____
// |  \/  |           (_)      |  ____|                        / ____|_     _
// | \  / | __ _  __ _ _  ___  | |__   _ __  _   _ _ __ ___   | |   _| |_ _| |_
// | |\/| |/ _` |/ _` | |/ __| |  __| | '_ \| | | | '_ ` _ \  | |  |_   _|_   _|
// | |  | | (_| | (_| | | (__  | |____| | | | |_| | | | | | | | |____|_|   |_|
// |_|  |_|\__,_|\__, |_|\___| |______|_| |_|\__,_|_| |_| |_|  \_____|
//                __/ | https://github.com/Neargye/magic_enum
//               |___/  version 0.9.5
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// SPDX-License-Identifier: MIT
// Copyright (c) 2019 - 2024 Daniil Goncharov <neargye@gmail.com>.
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef MAGIC_ENUM_IOSTREAM_HPP
#define MAGIC_ENUM_IOSTREAM_HPP

#include <iosfwd>
#include <istream>
#include <optional>

#include "magic_enum/magic_enum.hpp"

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

#endif // MAGIC_ENUM_IOSTREAM_HPP
