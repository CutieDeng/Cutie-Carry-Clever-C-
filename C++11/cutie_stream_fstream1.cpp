#include <iosfwd>
#include <fstream> 

#include <iostream> 

class new_line {
    public: ~new_line() {std::cout << "--------------------" << std::endl << std::endl; }
}; 

int main() {

    // 上文中一直没有提到 close 函数的使用描述，但事实在一直在频繁使用 close 进行文件资源的释放。
    // 让我们看看，close 到底是一个什么样的东西吧。

    // 首先，close 是 fstream 特有的方法，而不是一般的 stream 的方法。
    // 这样的方法有如下三个：is_open, open, close. 
    // is_open 是一个返回值为 bool 的方法，描述了该 stream 是否与某个文件被绑定在一起。

    std::fstream alog ("a.log", std::ios::app); 

    // 在我们直接使用 fstream constructor 的时候，我们会在构造出 fstream 对象实例的同时，同时将其与某个文件绑定在一起！

    using std::cout; 
    cout.setf(std::ios::boolalpha); 
    cout << "Is alog open? " << alog.is_open() << std::endl; 
    new_line(); 

    // 当我们试图关闭该 fstream, 再次调用该方法回答我们的询问！
    
    alog.close(); 
    cout << "We close alog. " << std::endl << "Is alog open? " << alog.is_open() << std::endl; 
    new_line(); 

    // 当我们又再次试图再次关闭 alog, what would happen? 

    alog.close(); 
    cout << "We close alog again. " << std::endl << "Is alog open? " << alog.is_open() << std::endl; 
    new_line(); 



    // 可以看出，对一个已经关闭的 fstream, 再次进行关闭，并不会导致其它事情发生。
    // 那么，让我们看看 open 方法吧！
    // 由于我们在上一次文件中便已经多次使用了 fstream.open 进行打开文件，所以我们在此只研究几种特殊情形。

    // 当 fstream 以非 out 形式打开一个不存在的文件时：
    // 将要以下几种情况发生：

    // 当使用 in 模式打开一个不存在的文件时：

    alog.open("_unexisted", std::ios::in); 
    cout << "Algo attempt the open a file in 'r' mode, which is unexisted. " << std::endl 
        << "Is alog open? " << alog.is_open() << std::endl; 
    alog.close(); 
    new_line(); 



    // 当使用 in | out 模式打开一个不存在的文件时：

    alog.open("_unexisted", std::ios::in | std::ios::out); 

    cout << "Alog attempt the open an unexisted file using the file mode 'r+'. " << std::endl
        << "Is alog open? " << alog.is_open() << std::endl; 
    alog.close(); 
    new_line(); 

    // 值得注意的是，在 cppreference.com 的描述中，该情况应当会触发一个 Error. 
    // 然而，在实践中，笔者未能看到理想的结果。
    // 没能成功打开仅仅只是在 is_open 中给出了 false 的回答，并不存在一个需要 catch 的错误或异常。

    // 除了这两种打开方式以处，其它打开方式都以 out 为核心，即在发现文件找不到的情形下，将会自行创建一个与描述相对应的文件。



    // 关于 stream 还有一个需要补充的描述：
    // 笔者建议使用 constructor, destructor 来控制系统资源。
    // 即在 fstream 构造时便指定其对应，应当绑定的文件名称。
    // 而在 fstream 的生命周期结束时，程序会自动调用 destructor 销毁该对象——对 fstream 对象来说，close 方法会被自动调用。
    // 即我们可以放心使用 fstream 对象而不必担心内存与系统资源回收的问题。    

    // 此外，在本节中的 new_line 函数，便使用了对象在 C++ 中的生命周期模型的设计实现的分隔符。
}