#include <iostream> 

int main() {
    if consteval {
        return 0; 
    } else {
        std::cout << "This is a false main method. \n";
    }
}