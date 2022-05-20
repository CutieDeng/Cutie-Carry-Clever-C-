#include <iostream> 
#include <sstream> 

// 一般常用 NDEBUG 标识符表示关闭 debug 信息——而不定义这个标识符来打开相关的开关。 
#define NDEBUG

// 描述学生相关信息的头文件！ 
// 里面简要描述了一个存储学生相关信息的一个类
#include "student_info.hpp"

// 处理对查询学生的询问函数。
void do_query();

// 处理查询所有学生的询问。
void do_show_all(); 

// 处理借书记录的添加。
void do_borrow_book();

// 处理添加新的读者描述。
void do_add_student();

// 学生信息记录 
std::list<student_info> students_list; 

// 导入常用的字面量 
using namespace std::literals;

int main() {

    // 输出 CLI 展示的标题。 
    std::cout << "--- Library Student Management System ---" << std::endl; 
    
    // 输出程序运行的 debug 信息。 
    // 记录本 executable file 是通过哪个文件编译而来。
    #ifndef NDEBUG
    std::cerr << "This program is compiled by the file " __FILE__ << std::endl; 
    #endif

    // 定义一个简单的枚举类，描述以下几种枚举值。
    // EXIT: 退出该应用交互界面——即退出程序。
    // ADD STUDENT: 添加新的读者信息。
    // ADD BORROWED BOOK: 添加新的借书记录。
    // QUERY_STUDENT： 询问学生的相关借书记录。
    // QUERY_ALL: 询问所有的借书记录。 
    // NOTHING: 空描述 
    enum class choose: unsigned {
        EXIT = 0,
        ADD_STUDENT = 1,
        ADD_BORROWED_BOOK = 2, 
        QUERY_STUDENT = 3, 
        QUERY_ALL = 4, 
        NOTHING = 5,
    };

    // 默认将 choose 初始化为 choose::NOTHING, 意为不执行任何动作。
    choose choose = choose::NOTHING; 

    // 进入无限循环，以便便于进行用户交互。 
    while (choose != choose::EXIT) {

        // 输出基本的交互信息，描述可识别的命令。 
        std::cout << std::endl << std::endl 
            << "==========" << std::endl 
            << "Enter an integer to describes the operation you want to execute: " << std::endl 
            << "1: Add a new student in the manage system. " << std::endl 
            << "2: Add a borrowed book for a student. " << std::endl 
            << "3: Query the concrete information of a student. " << std::endl 
            << "4: Show all students information. " << std::endl 
            << "0: Save and EXIT the system. " << std::endl << std::endl; 
        
        // 从用户输入中提取有效的输入信息。 
        choose = ({int input; std::cin >> input; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); (!std::cin) ? 
            std::cin.clear(), std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'), choose::NOTHING :
                ((input < 0 || input > 4) ? choose::NOTHING : 
            static_cast<enum choose>(input)); });
         
        // 输出当前选择的执行命令，以便 debug 时观察 
        #ifndef NDEBUG 
        std::cerr << "The actual value of choose is " << static_cast<unsigned>(choose) << std::endl; 
        #endif

        // 根据 choose 内容跳转到对应的可执行方法。  
        switch (choose) {
            case choose::QUERY_STUDENT: 
                do_query(); 
                break; 
            case choose::QUERY_ALL: 
                do_show_all(); 
                break; 
            case choose::ADD_BORROWED_BOOK: 
                do_borrow_book(); 
                break; 
            case choose::ADD_STUDENT: 
                do_add_student(); 
                break; 
            case choose::EXIT: 
                std::cout << "--- Save the information in the res files. ---" << std::endl; 
                break; 
            case choose::NOTHING: break;
        }
    }
}

void do_query() {

    // 输出基本的询问帮助支持。
    std::cout << std::endl << "------ Query Student Information ------" << std::endl; 
    std::cout << "Please enter the student name to query the information: " << std::endl; 

    // 尝试读入相关的询问学生姓名. 
    std::string query_stu_name; 
    std::getline(std::cin, query_stu_name); 

    // 增加对当前模块的退出支持。 
    if (query_stu_name == "[[exit]]"sv) {
        std::cout << std::endl << "Exit the query student information module. " << std::endl; 
        return ; 
    }

    // 搜索是否存在对应的 name 信息，并且取出匹配的第一个值 
    if (auto s = std::find_if(students_list.cbegin(), students_list.cend(), [&](auto s){return s.name == query_stu_name; }); 
        s != students_list.cend()) {
            std::cout << std::endl << "Find the student successfully: " << std::endl 
                << "\t\t" << *s << std::endl; 
        } else {
            std::cout << std::endl << "Fails to find the specific student. " << std::endl; 
        }
}

// 正在加入新的学生 
void do_add_student() {

    // 
    std::cout << std::endl << std::endl << "--- Add student module ---" << std::endl; 

    std::string name; 

    if (false) {
        repeat_determine_name: 
        std::cout << std::endl << "Back to the name definition process, please enter his/her name: " << std::endl;    
    } else 
        std::cout << std::endl << "Enter the student's name: " << std::endl; 
    
    std::getline(std::cin, name); 

    auto display_name = [&name](){ std::cout << std::endl << "The student's name is " << name << ", you can input [[change name]] to change the name! " << std::endl; }; 

    std::string identity_code; 
    if (false) {
        repeat_determine_code: 
        display_name(); 
        std::cout << std::endl << "Back to the identity code determination process, please enter the identity code: " << std::endl; 
    } else {
        display_name();
        std::cout << std::endl << "Enter the identity code: " << std::endl; 
    }
    std::getline(std::cin, identity_code); 
    if (identity_code == "[[change name]]"sv)
        goto repeat_determine_name;
    else if (identity_code == "[[exit]]"sv) {
        std::cout << std::endl << "------ Exit the Student Register Module ------" << std::endl << std::endl; 
        return ; 
    }

    auto display_identity_code = [&identity_code] {std::cout << std::endl << "The student's identity code is: " << identity_code << ". You can input [[change identity-code]] to change it! " << std::endl; }; 

    std::string graduated_year; 
    if (false) {
        repeat_graduate_year: 
        display_identity_code(); 
        std::cout << std::endl << "Back to the graduated year config process, please enter a 4-width number to express the graduated time. " << std::endl; 
    } else {
        display_identity_code(); 
        std::cout << std::endl << "Enter a 4-width number to express the graduated time. " << std::endl; 
    }
    std::getline(std::cin, graduated_year); 

    students_list.emplace_back(std::move(name), std::move(identity_code), std::move(graduated_year)); 
    
    std::cout << std::endl << "Successfully create a student"; 
}

void do_borrow_book () {
    std::cout << std::endl << "------ Student Borrow a Book ------" << std::endl;  
    if (students_list.empty()) {
        std::cout << "The system now doesn't contain a student. " << std::endl 
            << "You cannot add a student borrow record! " << std::endl; 
        return ;
    }

    std::string student_name; 
    if (false) {
        repeat_student_name: 
        std::cout << std::endl << "Again type the student name please: " << std::endl; 
    } else if (false) {
        repeat_missing_student: 
        std::cout << std::endl << "Cannot fetch the proper student in the student set. " << std::endl 
            << "Please again input the student's name: " << std::endl;
    } else {
        std::cout << std::endl << "Enter the student name to add a borrow record. " << std::endl; 
    }

    std::getline(std::cin, student_name); 

    if (student_name == "[[exit]]"sv) {
        exit_the_function: 
        std::cout << std::endl << "------ Exit the Borrow Book Record Module ------" << std::endl << std::endl; 
        return ; 
    }
    if (auto s = std::find_if(students_list.begin(), students_list.end(), [&student_name](auto s){return s.name == student_name;}); s == students_list.end()) {
        goto repeat_missing_student; 
    } else {
        std::cout << std::endl << "Read the name successfully, the new borrow record would add to this student. " << std::endl; 

        std::string book_name; 
        if (true) {
            std::cout << std::endl << "The borrowed book record records the student name: " << student_name << ". Use [[change student]] can change the student you choose. " << std::endl; 
            std::cout << std::endl << "Please enter the name of the borrowed book: " << std::endl; 
        } else {
            repeat_book_name_input: 
            std::cout << std::endl << "Back to the book name input information, pls input the name of this borrowed book. " << std::endl;  
        }

        std::getline(std::cin, book_name); 
        
        if (book_name == "[[change student]]"sv) {
            goto repeat_student_name; 
        } else if (book_name == "[[exit]]"sv) {
            goto exit_the_function;
        }

        s->borrowed_books.push_back(book_name); 

        std::cout << std::endl << "You input the book name: " << book_name << std::endl 
            << "This record successfully adds. " << std::endl; 

    }
} 

void do_show_all () {
    std::cout << std::endl << "------ Students Information List ------" << std::endl; 
    for (auto &&s: students_list) {
        std::cout << std::endl << s << std::endl; 
    }
    std::cout << std::endl << "------ End of Students List ------" << std::endl; 
}