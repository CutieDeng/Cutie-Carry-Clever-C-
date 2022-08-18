#include <iostream> 
#include "precision.hpp"

// using namespace percision; 

int main() {
    using precision::operator""_fmt; 
    int32_t ans = "hello world, my name is for futie deng. "_fmt; 
    std::cout << ans << std::endl; 
}