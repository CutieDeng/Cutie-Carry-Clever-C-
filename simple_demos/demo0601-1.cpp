#include <iostream> 
#include <string> 
#include <memory> 

using std::shared_ptr, std::make_shared; 

class HasName: public std::enable_shared_from_this<HasName> {
    public: 
        /** 
         * name is the unique method for someone who has the name. 
         * 
         * Invoke this method can get the string visitor, which would keep the result alive till the object lives. 
         */ 
        virtual std::string_view name() const = 0; 
        virtual ~HasName() = default; 
}; 

class Wolf : public HasName{
    private: 
        std::string m_name {"a wolf"}; 
    public: 
        std::string_view name() const override {
            return m_name; 
        } 
}; 

int main() {
    shared_ptr<HasName> someone = make_shared<Wolf>();
    std::cout << someone->name() << " wang! \n"; 
    auto other = someone->shared_from_this(); 
    std::cout << other->name() << " wang! \n"; 
    Wolf other2; 
    auto o2 = other2.weak_from_this(); 
    std::cout.setf(std::ios::boolalpha); 
    std::cout << bool(o2.expired()) << ". \n"; 
    auto t = o2.lock(); 
    std::cout << bool(t) << '\n'; 
}