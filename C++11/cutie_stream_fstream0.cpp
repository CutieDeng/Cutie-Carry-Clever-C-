#include <fstream> 

#include <iostream> 
#include <cstdlib> 

void f_() {
    std::cout << "--------------------" << std::endl << std::endl; 
}

int main() {

    // 让我们直接输出最经典的一句 programming sentence 吧：
    
    using std::cout ; 
    cout << "Hello World" << std::endl; 
    f_(); 

    // 然而，本段代码计划正式讲解 stream 处理. 在这过程中我会试图描述清楚以下几件事情：
    // 0. The fstream constructor methods. 
    // 1. close 函数的使用
    // 2. 逐字节读入方法，二进制文件处理



    // 首先，fstream 的构造器有以下可选的参数构成：
    // filename: 文件名
    // open mode: 打开模式，分别有 ios::app （追加）, ios::ate （自动将指针指向文件尾）, 
    //      ios::binary （以二进制的形式打开）, ios::in/out （输入/输出形式）, ios::trunc （清空文件内容再打开）. 
    // open prot: 文件打开属性
    // 分为四个属性，普通文件访问；只读文件访问；隐藏文件访问；系统文件访问。

    std::ofstream out ("a.log", std::ios::app); 
    
    {
        // 反复运行该方法，能够不断在同目录 a.log 文件下追增新内容。
        // appending open mode 打开效果如上描述。

        std::string name, word; 
        cout << "What's your name? " << std::endl; 
        getline(std::cin, name); 
        cout << "What do you want to say? " << std::endl; 
        getline(std::cin, word); 
        
        if (std::cin) {
            out << "[" << name << "]: " << word << std::endl; 
        } else {
            cout << "[ERROR] Meet a input related problem. " << std::endl; 
        }
        f_(); 
    }



    // 那么，有人就要发问了，那既然 ios::app 描述了一种向文件追加内容的操作，那 ios::ate 在做什么呢？
    // 让我们来试试吧：

    out.close(); 
    out.open("not_appending.log", std::ios::ate); 

    {
        std::string name;
        cout << "What's your name? " << std::endl; 
        getline(std::cin, name); 

        srand(0); 
        int ans = rand() % 20;
        cout << "You can guess a number, whose absolute is less than 20: " << std::endl; 

        int gus; 
        std::cin >> gus;  

        if (std::cin) {
            if (gus == ans) {
                out << "Plyaer " << name << " guessd the value " << gus << ", surprisingly hit the answer. " 
                    << std::endl; 
            } else {
                out << "Player " << name << " guessed the value " << gus <<", but the actual answer is " << 
                    ans << ". " << std::endl; 
            }
        } else {
            out << "Player " << name << " haven't guessed any value. " << std::endl; 
        }
        f_(); 
    }

    // 经过一番试验，我们发现，仅仅使用 ios::ate 恐怕并不能达成我们的目的！
    // 当前打开的 not_appending.log 并不能达成我们的目标：向后追增内容。



    // 让我们试着拿到相关的文件指针信息吧！

    out.close(); 
    out.open("not_appending.log", std::ios::ate); 

    cout << "Open the file 'not_appending.log', the pointer index = " << out.tellp() << ". " << std::endl; 

    // 当然，当该文件为一个空文件时，我们得到的 index 当然是 0. 


    
    // 但当我们已经提前在其中写入一定字节信息的情形下，它的值又会是多少呢？

    out << "Hello World\n"; 

    out.close(); 
    out.open("not_appending.log", std::ios::ate); 

    cout << "After we input some words in this file, the pointer index = " 
        << out.tellp() << std::endl; 
    f_(); 
    
    // 我们惊讶地发现：它的值并没有发生改变！
    // 这似乎和 C++ standard 对 ios::ate 的解释有所冲突？

    // 经过我们对 document 的再次阅读，我们发现：
    // ios::ate 仅仅在 ios::in 的情形下才能奏效——置文件指针于末尾
    // 而 ios::app 则不得同 ios::in 同时便用。
    // 但它们真的只有这种不一样嘛？



    // 让我们来看看 not_appending.log 文件吧！
    // 如果我们试图输出 not_appending.log 的内容：

    out.close(); 
    std::ifstream in("not_appending.log"); 
    cout << "The content of the file: " << std::endl; 
    while (true) {
        std::string content; 
        getline(in, content); 
        if (!in)
            break; 
        cout << content; 
    }
    in.close(); 
    f_(); 

    // 我们惊讶地发现：not_appending.log 文件被置空了！！！
    // 也就是说，ios::ate + ios::out 将会置空一个文件。
    // 有人可能会说：「这有啥的，难道 ios::out 不会置空文件嘛？」
    // 当然，笔者也不知道，就让我们测试一下吧。
    


    out.open("not_appending.log"); 
    out << "Hello World!\n"; 
    out.close(); 

    out.open("not_appending.log"); 
    out << "Cruel\n"; 
    out.close(); 

    in.open("not_appending.log"); 
    cout << "We input Hello World, and then input Cruel in the file 'not_appending.log'. " << std::endl; 
    cout << "The content of it: " << std::endl; 

    while (true) {
        std::string content; 
        getline(in, content); 
        if (!in)
            break; 
        cout << content; 
    }
    f_(); 
    
    // 观察不难发现，未带有 ios::ate 参数的 iostream, 依旧在输出过程中保持了 truncate all file 的特性。

    // 让我们稍稍总结一下：
    // fstream 有 ios::in/ios::out 两种不同的打开方式。
    // 而在 ios::in 下，有 ios::ate(尾部读取打开) 和默认方式打开(头部读取打开). 
    // 在 ios::out 下，有 ios::app (追加形式写入) 和默认方式打开(删除全文后写入). 
}