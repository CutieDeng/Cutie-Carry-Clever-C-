#include <iostream> 
#include <memory> 

template <size_t v> 
class Base {
    public: 
    virtual void invoke() {
        std::cout << "Invoke base method. " << v << '\n'; 
    }
    virtual ~Base() {
        std::clog << "Invoke destructor -- Base " << v << ";\n"; 
    }
}; 

class Derived : public Base<0>, public Base<1> {
    public: 
    void invoke() override {
        Base<1>::invoke(); 
        Base<0>::invoke(); 
        std::cout << "Invoke Dervied! \n"; 
    }
}; 

int main() {
    std::cout << "The resource is totally moved! \n"; 
    std::unique_ptr<Base<0>> p = std::make_unique<Derived>(); 
    p->Base<0>::invoke(); 
    static_cast<Base<0> *>(p.get())->invoke(); 
    // Base<1> *p = ptr; 
}