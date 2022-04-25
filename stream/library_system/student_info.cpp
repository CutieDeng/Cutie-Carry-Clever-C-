#include "student_info.hpp"

#include <sstream> 

std::ostream &operator << (std::ostream &ans, student_info const &k) {
    // std::stringstream ans; 
    ans << "{name=" << k.name << ", identity-code=" << k.identity_code << ", borrowed-books: "; 
    if (k.borrowed_books.empty()) 
        ans << "(None)"; 
    else {
        ans << "["; 
        bool f {}; 
        for (auto &&s: k.borrowed_books) {
            if (!f) f = true; else ans << ", "; 
            ans << s; 
        }
        ans << "]";
    }   
    ans << ", graduated-year=" << k.graduated_year << "}";  
    return ans; 
}