#include <iostream> 

using std::ostream, std::cin, std::cout; 

template <typename T> 
ostream &operator<< (ostream &, T ); 

template <> 
ostream &operator<< (ostream &o, char const *p) {
    // return o.operator<<(p); 
    return std::operator<< (o, p); 
}

ostream &operator<< (ostream &o, char const *) {
    return std::operator<< (o, "Output a char const!"); 
}

int main() {
    // cout << "Hello World!"; 
    // operator<< (cout, "Hello World!"); 
    (operator<<) (cout, "Hello World!"); 
    endl(cout); 

    ::operator<< (cout, "Hello World!"); 
    endl(cout); 

    std::operator<< (cout, "Hello World!"); 
    endl(cout); 

    ::std::operator<< (cout, "Hello World!"); 
    endl(cout); 

    // operator<< <> (cout, "Hello World!"); 

    operator<< <char const *> (cout, "Hello World!"); 
    endl(cout); 

    cout.operator<<("Hello World!"); 
    endl(cout); 

    cout.operator<<("Hello World!"); 
    endl(cout); 

    using std::operator<<; // (ostream&, char const *); 
    cout << "Cruel World!"; 
    endl(cout); 

    operator<< (cout, "Cruel World!"); 
    endl(cout); 

    (operator<<) (cout, "Cruel World!"); 
    endl(cout); 

    // operator<< <char const *> (cout, "Cruel World!");
    // endl(cout); 

    // operator<< <char, std::char_traits<char>> (cout, "Cruel World!"); 
    // endl(cout); 

    ::operator<< (cout, "Cruel World!"); 
    endl(cout); 
}