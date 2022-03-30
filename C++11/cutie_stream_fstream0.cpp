#include <fstream> 

#include <iostream> 

void f_() {
    std::cout << "--------------------" << std::endl; 
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

    std::ofstream out ("b.out", std::ios::app); 
    
    {
        // 反复运行该方法，能够

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
    }


    
}