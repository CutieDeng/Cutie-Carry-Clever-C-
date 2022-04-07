#include <filesystem> 

#include <chrono> 
#include <iostream> 
#include <fstream> 
#include <iomanip>

class new_line {
    public: ~new_line() {std::cout << "--------------------" << std::endl << std::endl; }
}; 

template <typename T> 
std::string to_string(T const &t) {
    // auto c = std::chrono::system_clock::to_time_t (std::chrono::file_clock::to_sys (t)); 
    // return std::asctime(std::localtime(&c)); 
    return t; 
}

int main() {
    // 下面我们来看到如何使用 filesystem 来获取我们希望了解的文件的编辑时间的吧：
    // 首先我们考虑使用的 api 为 filesystem::last_write_time. 
    // 该方法的方法签名如下：
    // std::filesystem::file_time_type last_write_time(const std::filesystem::path& p); 
    // 当然，它还有另一个方法签名支持我们传入参数传出答案：
    // void last_write_time(const std::filesystem::path& p, \
                     std::filesystem::file_time_type new_time);
    // ???? 不过两个方法在此没有本质的不同表现，因此我们在此只考虑第一个方法的描述。

    // 该方法的 introduction: 
    // 1. Returns the time of the last modification of p, 
    // determined as if by accessing the member st_mtime of the POSIX stat
    //  (symlinks are followed). 
    // The non-throwing overload returns file_time_type::min() on errors.

    // 2. Changes the time of the last modification of p, as if by POSIX futimens (symlinks are followed).

    // 通过 introduction, 我们意识到，这两个方法，一个用于获取时间，一个用于修改时间。

    // 那么，让我们来试试吧！

    std::filesystem::path f = "a.log"; 

    // 向 a.log 输出一句 Hello World! 
    std::ofstream o (f.c_str()); 
    o << "Hello April's Day!\n"; 
    o.close(); 

    std::cout.setf(std::ios::boolalpha); 

    // 显然，我们刚刚试图写出了一个文件，那么，让我们来看看它的文件相关信息吧。
    {
        auto l_ = new_line(); 
        auto t = std::filesystem::last_write_time(f); 

        // 在此，我们获取了一个对象 t: std::filesystem::file_time_type 类型。
        // 此类型继承的是 std::chrono::time_point<trivialtype> 类型 -- version C++17 下

        // 在 mac 上的实验由于 to_sys 函数的缺失，暂时无法使用 cppreference 上所描述的 
        // std::chrono::system_clock::to_time_t( std::chrono::file_clock::to_sys()); 操作。

        // 经过漫长的实验，我们找到了一种更简捷的方式。
        
        auto t2 = std::chrono::file_clock::to_time_t(t); 
        
        // 此时，t2 应当为一个 time_t 类型，即一个 long 类型。（mac platform, a guess. ）

        std::cout << "The type of t2 is: " << typeid(t2).name() << std::endl; 
        std::cout << "Question: Is the type of t2 the same as long? " << std::is_same<decltype(t2), long>::value << std::endl; 
        // std::cout << (t2) << std::endl; 

        // 然后，不妨我们使用 std::localtime 函数来对其进行转化：
        // std::localtime 将一个 std::time_t* 变量转化为一个 std::tm* 变量。

        auto t3 = std::localtime(&t2); 

        std::cout << "The type of t3 is: " << typeid(t3).name() << std::endl; 

        // 那么，我们不得不考虑一个问题，该操作是否会创建一个新的变量给我们呢？还是一种重解释相同内存地址的实现？

        std::cout << "The address of t2: 0x" << std::hex << t2 << ", and the value of t3: 0x" << t3 << std::endl; 

        // 可见，该方法理应创建了一个新对象并将其所有权交付给了 t3. 
        // 让我们试试显示回收该内存看看吧。
        // 在此之前，不妨让我们先做个值复制～以保留我们的成果。
        auto t4 = *t3; 
        delete t3; t3 = nullptr; 

        // 接下来，让我们使用 t4 去做试着进行对应的值的获取吧：
        // 让我们看看 tm 类都有哪些属性可供我们调用！
        std::cout << "The special format of t4: " << std::asctime(&t4) << std::endl; 
        std::cout << "The year is: " << std::dec << t4.tm_year << std::endl; 
        std::cout << "The month is: " << t4.tm_mon << std::endl; 
        std::cout << "The day is: " << t4.tm_yday << std::endl; 
        std::cout << "The time: " << t4.tm_hour << ":" << t4.tm_min << ":" << t4.tm_sec << std::endl; 

        // 可以发现，tm_year 以 1900 年为基准，描述了若干的时间内容。
    }

    

}