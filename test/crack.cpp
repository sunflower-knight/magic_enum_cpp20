#include "iostream"
#include <string_view>

using namespace std;

template <auto V>
consteval string_view name() {
    return __FUNCSIG__;
}

enum hack{
    b5a7b602ab754d7ab30fb42c4fb28d82,
    d19f2e9e82d14b96be4fa12b8a27ee9f
};

int main() {
    constexpr auto n1 = name < hack::b5a7b602ab754d7ab30fb42c4fb28d82 > ();
    constexpr auto n2 = name < hack::d19f2e9e82d14b96be4fa12b8a27ee9f > ();
    std::cout << n2 << endl;
}
