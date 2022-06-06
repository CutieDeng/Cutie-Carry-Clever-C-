#include <iostream> 

int a; 

struct A {
    private: 
        inline static int a = 0; 
    public: 
        A() {
            std::clog << "a is " << a << '\n'; 
        }
}; 

int main() {
    a = 21; 
    A{}; 
}