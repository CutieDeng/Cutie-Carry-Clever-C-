#include <iostream> 

template <size_t v> 
class Base {
    public: 
    virtual ~Base() {
        std::clog << "Invoke destructor -- Base " << v << ";\n"; 
    }
}; 

class Derived : public Base<0>, public Base<1> {

}; 

int main() {
    std::cout << "The resource is totally moved! \n"; 
    Derived *ptr = new Derived(); 
    Base<1> *p = ptr; 
    delete p; 
}