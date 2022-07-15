#include <iostream> 

struct Simple {
    Simple() {
        std::cout << "Invoke Empty Constructor. \n"; 
    }
    Simple(Simple const volatile &) = default; 
    ~Simple() {
        std::cout << "Invoke the destructor. \n"; 
    }
}; 

Simple get() {
    // Simple start; 
    Simple const volatile second; 
    // return std::move(second); 
    return second; 
}

int main() {
    Simple a = get(); 
}