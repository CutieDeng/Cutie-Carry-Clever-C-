#include <iostream> 

#include "orderlib.hpp"

int main() {
    start(); 
    auto result = Stone::randomly_construct<0>(); 
    test(result);
}