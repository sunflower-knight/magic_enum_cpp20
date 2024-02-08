#ifndef MAGIC_ENUM_CORE_CONFIG_HPP
#define MAGIC_ENUM_CORE_CONFIG_HPP

/** @brief load all config information from config file "xxx.cfg"  */
#if defined(MAGIC_ENUM_CONFIG_FILE)
#include MAGIC_ENUM_CONFIG_FILE
#endif

/** @brief use your own optional/string/string_view in magic_enum */
#ifndef MAGIC_ENUM_USING_ALIAS_OPTIONAL
#include <optional>
#endif
#ifndef MAGIC_ENUM_USING_ALIAS_STRING
#include <string>
#endif
#ifndef MAGIC_ENUM_USING_ALIAS_STRING_VIEW
#include <string_view>
#endif

#include <array>
#include <cinttypes>
#include <limits>

/** support runtime assert when you use runtime interface */
#ifdef MAGIC_ENUM_NO_ASSERT
#  define MAGIC_ENUM_ASSERT(...) static_cast<void>(0)
#elif !defined(MAGIC_ENUM_ASSERT)
#  include <cassert>
#  define MAGIC_ENUM_ASSERT(...) assert((__VA_ARGS__))
#endif

/**
 * @MAGIC_ENUM_RANGE_MIN Enum value must be greater or equals than MAGIC_ENUM_RANGE_MIN. By default, MAGIC_ENUM_RANGE_MIN = -128.
 * If need another min range for all enum types by default, redefine the macro MAGIC_ENUM_RANGE_MIN.
 * @MAGIC_ENUM_RANGE_MAX Enum value must be less or equals than MAGIC_ENUM_RANGE_MAX. By default, MAGIC_ENUM_RANGE_MAX = 128.
 * If need another max range for all enum types by default, redefine the macro MAGIC_ENUM_RANGE_MAX.
 * @note [MAGIC_ENUM_RANGE_MIN,MAGIC_ENUM_RANGE_MAX] 左右闭区间
 */
#ifndef MAGIC_ENUM_RANGE_MIN
#  define MAGIC_ENUM_RANGE_MIN (-128)
#endif
#ifndef MAGIC_ENUM_RANGE_MAX
#  define MAGIC_ENUM_RANGE_MAX 127
#endif

static_assert(MAGIC_ENUM_RANGE_MAX > MAGIC_ENUM_RANGE_MIN, "MAGIC_ENUM_RANGE_MAX must be greater than MAGIC_ENUM_RANGE_MIN.");
static_assert((MAGIC_ENUM_RANGE_MAX - MAGIC_ENUM_RANGE_MIN) < (std::numeric_limits<std::uint16_t>::max)(), "MAGIC_ENUM_RANGE must be less than UINT16_MAX.");



/**
 * @inject std::optional string string_view for default
 */
namespace magic_enum
{
    // If need another optional type, define the macro MAGIC_ENUM_USING_ALIAS_OPTIONAL.
    #if defined(MAGIC_ENUM_USING_ALIAS_OPTIONAL)
    MAGIC_ENUM_USING_ALIAS_OPTIONAL
    #else
    using std::optional;
    #endif

    // If need another string_view type, define the macro MAGIC_ENUM_USING_ALIAS_STRING_VIEW.
    #if defined(MAGIC_ENUM_USING_ALIAS_STRING_VIEW)
    MAGIC_ENUM_USING_ALIAS_STRING_VIEW
    #else
    using std::string_view;
    #endif

    // If need another string type, define the macro MAGIC_ENUM_USING_ALIAS_STRING.
    #if defined(MAGIC_ENUM_USING_ALIAS_STRING)
    MAGIC_ENUM_USING_ALIAS_STRING
    #else
    using std::string;
    #endif
}

#endif
