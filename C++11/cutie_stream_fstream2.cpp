#include <fstream> 

#include <iostream> 
#include <string> 
#include <memory> 

struct newline { ~newline() {std::cout << "====================" << std::endl << std::endl; } };

int main() {
    
    // 本章的核心内容是：二进制语境下的文件 IO. 
    // 那么，让我们先看看标准库提供的函数吧：
    // 本次重点讨论的函数有以下四个：put, write (for output). get, read (for input). 

    std::fstream f ("a.log", std::ios::out | std::ios::binary); 

    // 我们不访试着输出 Hello World \n 到 a.log 文件中进行尝试。

    // sizeof s 会求出 s 数组的长度，但我们不计划输出 s 的最后一位（那是一个 \0 字符，因此我们只描述少了这一位的字符串。

    char const s[] = "Hello World \n"; 
    f.write(s, sizeof s - 1); 

    f.close(); 

    // 由于我们输入的都是英文字符，所以其对应产生的编码信息能够使用普通的文本格式解码。

    f.open("a.log", std::ios::in); 
    std::cout << "The content of the file a.log: " << std::endl; 
    std::string p; 
    while (true) {
        getline(f, p); 
        if (!f)
            break; 
        std::cout << p << std::endl; 
    }
    f.close(); 
    newline(); 

    // 下面我们试着用逐字节逐字节的方式进行解码。 
    // 为了让该过程更直观，我在解码时将选择只直接解码大小写字母，其余编码均使用 literal值表示。

    // 使用 binary 进行二进制的读写操作是 cppreference 的建议，但我没有感觉到这个标签的必要性。
    // 请阅读 https://en.cppreference.com/w/cpp/io/c/FILE#Binary_and_text_modes 了解更多关于 binary mode 内容。

    f.open("a.log", std::ios::in | std::ios::binary); 
    std::unique_ptr<char []> cs = std::make_unique<char []>(50); 
    f.read(reinterpret_cast<char *>(cs.get()), 50); 
    auto read_cnt = f.gcount(); 
    for (auto i {0}; i < read_cnt; ++i) {
        if (cs[i] >= 'a' && cs[i] <= 'z') {
            std::cout << cs[i]; 
        } else if (cs[i] >= 'A' && cs[i] <= 'Z') {
            std::cout << cs[i]; 
        } else {
            std::cout << "(" << std::hex << (int )cs[i] << ")" << std::dec; 
        }
    }
    std::cout << std::endl; 
    f.close(); 
    newline(); 

    // 当使用 read 进行读入的时候，其应当传入两个参数：istream.read(char *, std::streamsize ); 
    // 其第一个参数是一个 char *, 即字节类型的指针，表示你希望将读入的内容放在什么位置。
    // 其第二个参数则是对读入长度的最大限制，以避免其读入导致代码安全漏洞. 
    // 显而易见，该函数应当有一个返回值，来描述实际读入的内容长度。
    // 然而，iostream 的设计可能有点奇怪吧，它将该返回值放入了一个函数中，待我们调用以便获得返回值。
    // 即 gcount 函数。

    // 下面我们来研究多次调用 read 时 gcount 返回值的变化。

    // 重置 cs 的内容，以便于不干扰下一次实验. 
    f.open("a.log", std::ios::in | std::ios::binary); 
    memset(reinterpret_cast<char *>(cs.get()), 0, 50); 

    f.read(reinterpret_cast<char *>(cs.get()), 4); 
    std::cout << "Reopen the file a.log, and invoke the read(4) to read the information to cs. " << std::endl; 

    auto size = f.gcount(); 
    std::cout << "f.gcount() = " << size << std::endl; 
    std::cout << "Again invoke the method f.gount(): " << f.gcount() << std::endl; 

    std::cout << "The content of cs: " << std::endl; 
    for (auto i {0}; i < size; ++i) {
        std::cout << cs[i]; 
    }
    std::cout << std::endl; 

    std::cout << "Then invoke read(5). " << std::endl; 
    f.read(reinterpret_cast<char *>(cs.get()) + size, 5); 

    std::cout << "Invoke the method f.gount(): " << f.gcount() << std::endl; 
    size += f.gcount(); 

    std::cout << "The content of cs: " << std::endl; 
    for (auto i {0}; i < size; ++i) {
        std::cout << cs[i]; 
    }
    std::cout << std::endl; 
    f.close(); 
    newline(); 

    // 最后，put, get 方法的使用与 read, write 类似，且输入、传出参数为一个 char 的字面量。
    // 函数使用更为简单，相关实验不在这里展开。
}  