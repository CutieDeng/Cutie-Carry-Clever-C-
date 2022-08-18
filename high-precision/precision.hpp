#include <cstdlib> 
#include <vector> 
#include <exception> 
#include <numeric> 
#include <cassert> 

namespace precision {
    template <size_t N> 
    struct StaticStr {
        using This = StaticStr; 
        constexpr static size_t LENGTH = N; 
        consteval explicit(false) StaticStr(char const (&c)[N]) {
            for (size_t i = 0; i < N; ++i) {
                c_[i] = c[i]; 
            }
        }
        char c_[N]; 
        consteval char const *str() const {
            return c_; 
        }
        consteval char const &operator[] (size_t index) const {
            // static_assert (index < LENGTH); 
            assert (index < LENGTH); 
            return c_[index]; 
        }
    }; 

    template <StaticStr s> 
    consteval int32_t operator ""_fmt() {
        int32_t result {}; 
        for (size_t i = 0; i < decltype(s)::LENGTH; ++i) {
            if (s[i] == 'f') {
                assert (result != std::numeric_limits<int32_t>::max()); 
                result += 1; 
            }
        }
        return result; 
    }

    // class uint128_t; 
    // class int128_t; 
    class Integer {
    }; 
}