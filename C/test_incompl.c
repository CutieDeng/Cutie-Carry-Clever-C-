#include <stdlib.h> 
#include <stdio.h> 

struct MyArray {
    size_t length; 
    char element[]; 
}; 

int main() {
    struct MyArray array; 
    printf ("Create an array: MyArray! \n");
    array.element = &array; 
}