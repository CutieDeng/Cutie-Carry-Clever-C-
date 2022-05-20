#ifndef __VECTOR1_H_ 
#define __VECTOR1_H_ 

#include <string.h> 
#include <stdlib.h> 

struct IntVector; 

/** 
 * The constructor of int vector! 
 */ 
struct IntVector *new_int_vector(); 

/** 
 * Push the value to the end of this vector! 
 */ 
void vector_push_back(struct IntVector *, int ); 

/** 
 * Pop the value of the end of the vector. 
 */ 
void vector_pop_back(struct IntVector *); 

/** 
 * Get the value using the index. 
 */ 
int vector_at(struct IntVector *, size_t ); 

/** 
 * Remove the specific value according to the index. 
 */ 
void vector_remove(struct IntVector *, size_t ); 

/** 
 * Get the size of the vector. 
 */ 
size_t vector_size(struct IntVector *); 

/** 
 * Get the first element of vector. 
 */ 
int vector_begin(struct IntVector *); 

/** 
 * Get the last element of vector. 
 */ 
int vector_end(struct IntVector *); 

/** 
 * Set the value using an index. 
 */ 
void vector_set_at(struct IntVector *, size_t, int ); 

/** 
 * Delete the vector information. 
 */ 
void delete_int_vector(struct IntVector *); 

#endif 