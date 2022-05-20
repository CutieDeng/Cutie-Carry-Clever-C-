#include <iostream> 
#include <string> 

struct demo {
    private: 
    std::string name; 
    public: 
    demo(std::string name = "Unnamed"); 
    operator std::string() const; 
}; 

demo::demo(std::string name): name(name) {}

demo::operator std::string() const {
    return name; 
}

int main() {
    demo basic; 
    std::cout << (std::string)basic << std::endl; 
}