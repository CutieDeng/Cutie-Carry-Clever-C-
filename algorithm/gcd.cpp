#include <iostream> 

template <typename T> 
T gcd(T a, T b) {
    if (!a) 
        if (b) return std::move(b); 
        else throw std::logic_error("Cannot find gcd between two zero values. "); 
    while (b) {
        auto r = a % b; 
        a = std::move(b); 
        b = std::move(r); 
    }
    return std::move(a); 
}

int main() {
    auto t = gcd(2, 4); 
    std::cout << t << "\n"; 
}