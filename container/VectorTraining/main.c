#include "Vector1.h" 

#include <stdio.h> 
#include <assert.h>

#define assert_with(bool_exp, my_test_statement) do {\
    printf(my_test_statement "\n"); \
    assert (bool_exp); \
    printf ("Test successfully! \n\n"); \
    } while (0) 

int main() {
    printf ("Start this program! \n\n");  
    typedef struct IntVector IVR; 

    IVR *v = new_int_vector(); 

    assert_with(v, "Test the pointer value is null or not, as the invokation of method 'new_int_vector'. ");

    assert_with(vector_size(v) == 0, "Test the element number in vector. "); 

    vector_push_back(v, 7); 
    assert_with(vector_size(v) == 1, "Push '7' to the int vector, and test the size of it. "); 
    assert_with(vector_begin(v) == 7, "Test the start of the vector is 7. "); 
    assert_with(vector_end(v) == 7, "Test the end of the vector is 7. "); 

    vector_pop_back(v); 
    assert_with(vector_size(v) == 0, "Pop the value from the int vector, and test the value of it! "); 
}