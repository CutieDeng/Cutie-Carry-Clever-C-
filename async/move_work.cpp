#include <iostream> 

#include "orderlib.hpp"

int main() {
    start(); 
    auto result = Stone::randomly_construct<3>(); 
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (result->at(j).get_prior() > result->at(j+1).get_prior()) 
                swap(result->at(j), result->at(j+1)); 
        }
    }
    test(result);
}