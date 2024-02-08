#ifndef MAGIC_ENUM_CORE_CHECK_HPP
#define MAGIC_ENUM_CORE_CHECK_HPP

namespace magic_enum
{
    #define MAGIC_ENUM_VERSION_MAJOR 0
    #define MAGIC_ENUM_VERSION_MINOR 9
    #define MAGIC_ENUM_VERSION_PATCH 5

    // Checks magic_enum compiler compatibility.
    #if defined(__clang__) && __clang_major__ >= 6 || defined(__GNUC__) && __GNUC__ >= 11 || defined(_MSC_VER) && _MSC_VER >= 1910 || defined(__RESHARPER__)
    #  undef  MAGIC_ENUM_SUPPORTED
    #  define MAGIC_ENUM_SUPPORTED 1
    #endif

    #if defined(MAGIC_ENUM_SUPPORTED) && MAGIC_ENUM_SUPPORTED || defined(MAGIC_ENUM_NO_CHECK_SUPPORT)
    constexpr bool is_magic_enum_supported = true;
    #else
    constexpr bool is_magic_enum_supported = false;
    static_assert(is_magic_enum_supported, "magic_enum: Unsupported compiler Url Here");
    #endif

    using char_type = typename std::string_view::value_type;
    static_assert(std::is_same_v<std::string_view::value_type,std::string::value_type>,
    "magic_enum::customize requires same string_view::value_type and string::value_type");
    static_assert([] {
        if constexpr(std::is_same_v<char_type,wchar_t>) {
            constexpr const char c[]     = "abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789|";
            constexpr const wchar_t wc[] = L"abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789|";
            static_assert(std::size(c) == std::size(wc),
                          "magic_enum::customize identifier characters are multichars in wchar_t.");

            for(std::size_t i = 0; i < std::size(c); ++i) {
                if(c[i] != wc[i]) {
                    return false;
                }
            }
        }
        return true;
    }(), "magic_enum::customize wchar_t is not compatible with ASCII.");
}

#endif // MAGIC_ENUM_CORE_CHECK_HPP
