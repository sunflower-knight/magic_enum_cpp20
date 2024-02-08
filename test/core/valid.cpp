// TEST_CASE("valid_enum") {
//     //enum Forward1;
//     enum Forward2 : uint32_t;
//     enum class Forward3;
//     enum class Forward4 : uint32_t;
//     enum Empty1 {};
//     enum Empty2 : uint32_t {};
//     enum class Empty3 {};
//     enum class Empty4 : uint32_t {};
//
//     //REQUIRE(magic_enum::detail::is_reflected_v<Forward1, as_flags<true>>);
//     //REQUIRE(magic_enum::detail::is_reflected_v<Forward1, as_flags<false>>);
//     REQUIRE(magic_enum::detail::is_reflected_v<Forward2, as_flags<true>>);
//     REQUIRE(magic_enum::detail::is_reflected_v<Forward2, as_flags<false>>);
//     REQUIRE(magic_enum::detail::is_reflected_v<Forward3, as_flags<true>>);
//     REQUIRE(magic_enum::detail::is_reflected_v<Forward3, as_flags<false>>);
//     REQUIRE(magic_enum::detail::is_reflected_v<Forward4, as_flags<true>>);
//     REQUIRE(magic_enum::detail::is_reflected_v<Forward4, as_flags<false>>);
//     REQUIRE(magic_enum::detail::is_reflected_v<Empty1, as_flags<true>>);
//     REQUIRE(magic_enum::detail::is_reflected_v<Empty1, as_flags<false>>);
//     REQUIRE(magic_enum::detail::is_reflected_v<Empty2, as_flags<true>>);
//     REQUIRE(magic_enum::detail::is_reflected_v<Empty2, as_flags<false>>);
//     REQUIRE(magic_enum::detail::is_reflected_v<Empty3, as_flags<true>>);
//     REQUIRE(magic_enum::detail::is_reflected_v<Empty3, as_flags<false>>);
//     REQUIRE(magic_enum::detail::is_reflected_v<Empty4, as_flags<true>>);
//     REQUIRE(magic_enum::detail::is_reflected_v<Empty4, as_flags<false>>);
// }
