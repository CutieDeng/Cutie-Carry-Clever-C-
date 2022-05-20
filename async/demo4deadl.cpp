#include <iostream> 
#include <mutex> 
#include <thread>

auto lock_two(auto &a, auto &b) {
    using namespace std::literals;
    std::this_thread::sleep_for(0.7s);
    auto l4 = std::scoped_lock(a, b);  
    auto to_pout = "I have already lock them two already! \n"s; 
    for (auto k: to_pout) {
        std::cerr << k; 
        std::this_thread::sleep_for(18ms); 
    }
    return ; 
}

int main() {
    std::mutex a, b; 
    lock_two(a, b); 
    lock_two(b, a); 
    std::thread f1([&]{lock_two(a, b); }); 
    std::thread f2([&]{lock_two(b, a); }); 
    f1.join(); 
    f2.join(); 
}

