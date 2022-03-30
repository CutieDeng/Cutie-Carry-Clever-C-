#include <filesystem>

// filesystem 是描述文件系统的库，在 C++ 17 中被纳入 std::filesystem 命名空间中。
// 本节内容讲解了 filesystem 的核心类 path 的使用，和其相关的 relative, absolute, canonical 函数。
// 同时讲解、使用了 exists, file_size 函数。

#include <iostream> 
#include <sstream> 

void f_() {
    std::cout << "--------------------" << std::endl << std::endl; 
}

int main() {

    // 使用这个库，我们可以先学习使用 path 类来描述对应路径上的文件。　

    using std::filesystem::path; 

    path this_file (__FILE__); 

    std::cout << "The file name of this code file: " << this_file << std::endl; 
    std::cout << "The absolute file name of this code file: " << 
        std::filesystem::absolute(this_file) << std::endl; 
    std::cout << "The canonical name of this code file: " << 
        std::filesystem::canonical(this_file) << std::endl; 
    f_(); 

    // 运行代码。
    // 发现：absolute path 和 canonical path 相同。
    // 当然，事情并不这样。



    // 如果我们的文件是在一个二级以上的文件夹中，我们可以写出这样的代码。

    path grandparent_dir ("../.."); 
    
    std::cout << "The grandparent of the program: " << grandparent_dir << std::endl; 
    std::cout << "The grandparent absolute file name: " << 
        std::filesystem::absolute(grandparent_dir) << std::endl; 
    std::cout << "The grandparent canonical file name: " << 
        std::filesystem::canonical(grandparent_dir) << std::endl; 
    f_(); 

    // 可以看出，absolute path 仅仅是对 path 路径的拼接，而 canonical path 则包括对其进行适当的解析、折叠。



    // 那么，如果我们让它不断返回到根路径，会怎么样呢？

    path null_path ("/../.."); 

    std::cout << "The null absolute path: " << std::filesystem::absolute(null_path) << std::endl; 
    std::cout << "The null canonical path: " << std::filesystem::canonical(null_path) << std::endl; 
    f_(); 

    // 在 mac 平台下的测试结果：同 terminal 结果，在 / 文件夹下访问父文件夹仍会得到 / 文件夹。



    // 那么，接下来我们便要开始得到对应路径下的文件了！
    // 首先，我们不妨先确定当前的路径是否存在对应的文件。

    path null_file_path ("./_no_this_file"); 

    std::cout.setf(std::ios::boolalpha); 
    std::cout << "Does the file (" << null_file_path << ") exist? " << std::filesystem::exists(null_file_path) << std::endl; 
    std::cout << "Does this file (" << this_file << ") exist? " << std::filesystem::exists(this_file) << std::endl; 
    f_(); 

    // 由于我们当前目录下并没有这样一个文件 _no_this_file, 因此该询问的值为 false. 
    // 而如果编译操作和运行操作在同一个路径下，那么其操作的值则为 true. 



    // 下面，我们开始询问文件的大小信息！
    // 特别一提，这也与我们接下来要做到的 Zip Compress Program 息息相关——我们应当高效地获取到对应的 file 
    // 的文件大小信息。

    // 第一种方式，使用 try-catch 语句进行处理，以区分获取文件大小的逻辑代码是否能正常运行。

    try {
        std::stringstream s; 
        s << null_file_path << "'s size is " << 
            std::filesystem::file_size(null_file_path) << " bytes" << std::endl; 
        std::cout << s.str(); 
    } catch (std::filesystem::filesystem_error const &) {
        std::cout << null_file_path << " cannot be got a size info. " << std::endl; 
    }

    // 第二种方式，提前使用分支结构进行检测。

    if (std::filesystem::exists(this_file)) {
        std::cout << "The file size of " << this_file << " is " << std::filesystem::file_size(this_file)
            << " bytes. " << std::endl; 
    } else {
        std::cout << "We cannot find " << this_file << ". " << std::endl; 
    }
    f_(); 
}