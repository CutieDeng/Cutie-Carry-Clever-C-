#include <iostream> 
#include <concepts>

// auto add(std::integral auto a, std::integral auto b) {
//     return a + b * 2; 
// }

// auto add (auto a, auto b) 
//     requires requires {
//         a + b; 
//     }
//     {
//         return a + b; 
//     }



template <typename T> 
concept Matrix = requires (T matrix) {
    { matrix[std::declval<size_t>()][std::declval<size_t>()] } -> std::convertible_to<T>;
};

template <typename A, typename B> 
auto add (A a, B b) {
    return a + b; 
}

int main() {
    auto x = add(2, 3);  
    auto y = add(4, 3L);
    std::cout << x << ", " << y << '\n';
}