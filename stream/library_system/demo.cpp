#include <iostream> 
#include <sstream> 
#include <optional>

#define NDEBUG

#include "student_info.hpp"

void do_query(); 
void do_show_all(); 
void do_borrow_book();
void do_add_student();

std::list<student_info> students_list; 

using namespace std::literals;

int main() {
    std::cout << "--- Library Student Management System ---" << std::endl; 
    
    #ifndef NDEBUG
    std::cerr << "This program is compiled by the file " __FILE__ << std::endl; 
    #endif

    enum class choose: unsigned {
        EXIT = 0,
        ADD_STUDENT = 1,
        ADD_BORROWED_BOOK = 2, 
        QUERY_STUDENT = 3, 
        QUERY_ALL = 4, 
        NOTHING = 5,
    };

    choose choose = choose::NOTHING; 

    while (choose != choose::EXIT) {
        std::cout << std::endl << std::endl 
            << "==========" << std::endl 
            << "Enter an integer to describes the operation you want to execute: " << std::endl 
            << "1: Add a new student in the manage system. " << std::endl 
            << "2: Add a borrowed book for a student. " << std::endl 
            << "3: Query the concrete information of a student. " << std::endl 
            << "4: Show all students information. " << std::endl 
            << "0: Save and EXIT the system. " << std::endl << std::endl; 
        
        choose = ({int input; std::cin >> input; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); (!std::cin) ? 
            std::cin.clear(), std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'), choose::NOTHING :
                ((input < 0 || input > 4) ? choose::NOTHING : 
            static_cast<enum choose>(input)); });
         
        #ifndef NDEBUG
        std::cerr << "The actual value of choose is " << static_cast<unsigned>(choose) << std::endl; 
        #endif

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
    std::cout << std::endl << "------ Query Student Information ------" << std::endl; 
    std::cout << "Please enter the student name to query the information: " << std::endl; 
    std::string query_stu_name; 
    std::getline(std::cin, query_stu_name); 

    if (auto s = std::find_if(students_list.cbegin(), students_list.cend(), [&](auto s){return s.name == query_stu_name; }); 
        s != students_list.cend()) {
            std::cout << std::endl << "Find the student successfully: " << std::endl 
                << "\t\t" << *s << std::endl; 
        } else {
            std::cout << std::endl << "Fails to find the specific student. " << std::endl; 
        }
}

void do_add_student() {
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