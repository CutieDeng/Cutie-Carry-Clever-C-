#pragma once 

#include <string> 
#include <list> 
#include <iosfwd>

struct student_info {
    std::string name, identity_code; 
    std::list<std::string> borrowed_books; 
    std::string graduated_year; 

    student_info(std::string &&name, std::string &&identity_code, std::string &&graduated_year): 
        name(std::move(name)), identity_code(std::move(identity_code)), graduated_year(std::move(graduated_year)), borrowed_books() {
    } 

    friend std::ostream &operator << (std::ostream &, student_info const &); 
}; 