#include <iostream> 

import graph; 

int main() {
    using namespace game; 
    graph::Graph test (3, 3, 6); 
    {
        auto rbounds = test.row(); 
        auto cbounds = test.col(); 
        for (decltype(rbounds) r = 0; r < rbounds; ++r) {
            for (decltype(cbounds) c = 0; c < cbounds; ++c) {
                if constexpr (std::same_as<decltype(test)::value_type, int>) {
                    if (c) 
                        putchar(' '); 
                    // printf ("%d", (int )test[r, c]); 
                    if (auto &&p = test.at(r, c); p) {
                        printf ("%d", p->get()); 
                    } else {
                        printf ("err"); 
                    }
                }
            }
            putchar('\n'); 
        }
    }
}