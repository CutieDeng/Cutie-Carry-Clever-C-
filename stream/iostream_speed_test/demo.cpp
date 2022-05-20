#include <iostream> 
#include <iomanip>
#include <cstdio> 
#include <chrono> 

void test_cout() {
    std::cout << "Prepare the printing! " << std::endl; 
    auto start_ins = std::chrono::system_clock::now(); 
    for (auto i = 0; i < 1'000'000; ++i) {
        std::cout << "[Main Function]: " << i << '\n';
    }
    std::cout.flush(); 
    auto dura = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::system_clock::now() - start_ins
    ); 
    std::clog << "std::cout costs: " << dura.count() / 1e6 << " ms. \n"; 
}

void test_for_loop_expand() {
    std::cout << "Prepare the printing! " << std::endl; 
    auto start_ins = std::chrono::system_clock::now(); 
    for (auto i = 0; i < 250'000; ++i) {
        std::cout << "[Main Function]: " << (i*4) << 
            "\n[Main Function]: " << (i*4+1) <<
            "\n[Main Function]: " << (i*4+2) <<
            "\n[Main Function]: " << (i*4+3) << '\n';
    }
    std::cout.flush(); 
    auto dura = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::system_clock::now() - start_ins
    ); 
    std::clog << "[forloop expand]std::cout costs: " << dura.count() / 1e6 << " ms. \n"; 
}

void test_printf() {
    printf("Prepare the printing! \n");

    auto start_ins = std::chrono::system_clock::now(); 
    for (auto i = 0; i < 1'000'000; ++i) {
        // std::cout << "[Main Function]: " << i << '\n';
        printf("[Main Function]: %d\n", i); 
    }
    auto dura = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::system_clock::now() - start_ins
    ); 
    std::clog << "printf costs: " << dura.count() / 1e6 << " ms. \n"; 
}

void test_expand_printf() {
    printf("Prepare the printing! \n");

    auto start_ins = std::chrono::system_clock::now(); 
    for (auto i = 0; i < 250'000; ++i) {
        // std::cout << "[Main Function]: " << i << '\n';
        printf("[Main Function]: %d\n[Main Function]: %d\n[Main Function]: %d\n[Main Function]: %d\n", i*4, i*4+1, i*4+2, i*4+3); 
    }
    auto dura = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::system_clock::now() - start_ins
    ); 
    std::clog << "[Forloop Expand]printf costs: " << dura.count() / 1e6 << " ms. \n"; 
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);

    test_printf(); 
    test_printf();
    test_printf();
    test_cout(); 
    test_cout(); 
    test_cout(); 
    test_expand_printf();
    test_expand_printf();
    test_expand_printf();
    test_for_loop_expand(); 
    test_for_loop_expand(); 
    test_for_loop_expand(); 
}