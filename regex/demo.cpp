#include <regex> 
#include <string> 
#include <iostream> 

int main() {
    using std::regex; 
    regex match_student_id (R"(1201\d{4})"); 
    using std::cin; 
    std::string input; 
    while (cin) {
        getline(cin, input);  
        if (!cin)
            break; 
        auto is_student_id = regex_match(input, match_student_id);
        if (is_student_id)
            std::cout << "Input \'" << input << "\" actually is a student ID! \n"; 
        else 
            std::cout << "Sorry, invalid input! \n"; 
    }
}