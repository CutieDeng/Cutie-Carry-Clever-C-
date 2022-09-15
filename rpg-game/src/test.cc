#include <iostream> 

import graph; 

int main() {
    using namespace game; 
    // puts("-----------"); 
    graph::Graph test (3, 3, 6); 
    {
        puts ("----------"); 

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

        puts ("----------"); 

        bool out = true; 
        for (int r = 0, c = 0;;) { 
            auto &&p = test.at(r, c); 
            if (!p) {
                if (out) 
                    break; 
                ++r; c=0; out=true; 
                putchar('\n'); 
            } else {
                if (!out) 
                    putchar(' '); 
                printf ("%d", p->get()); 
                ++c; 
                out = false; 
            }
        }
    }
}