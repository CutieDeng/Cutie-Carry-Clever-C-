#include "Vector1.h" 

struct IntVector {
    int *ar; 
    size_t length; 
    size_t capacity; 
    enum {
        CAPACITY_DEFAULT = 20, 
    }; 
}; 

struct IntVector *new_int_vector() {
    struct IntVector *result = malloc(sizeof(struct IntVector)); 
    result->ar = malloc(sizeof(int) * CAPACITY_DEFAULT);
    result->length = 0; 
    result->capacity = CAPACITY_DEFAULT; 
    return result; 
}

void vector_push_back(struct IntVector *this, int val) {
    if (this->capacity == this->length) {
        return ;    
    }
    this->ar[this->length++] = val; 
    return ;
}

void vector_pop_back(struct IntVector *this) {
    --this->length;
}

int vector_at(struct IntVector *this, size_t val) {
    if (this->length <= val) 
        return 0; 
    return this->ar[val]; 
}

void vector_remove(struct IntVector *this, size_t val) {
    if (this->length <= val) 
        return ; 
    --this->length; 
    for (size_t v = val; v < this->length; ++v) {
        this->ar[v] = this->ar[v+1]; 
    }
}

size_t vector_size(struct IntVector *this) {
    return this->length; 
}

int vector_begin(struct IntVector *this) {
    if (this->length) 
        return this->ar[0]; 
    else 
        return 0; 
}

int vector_end(struct IntVector *this) {
    if (this->length) 
        return this->ar[this->length - 1]; 
    else 
        return 0; 
}

void vector_set_at(struct IntVector *this, size_t index, int val) {
    if (index >= this->length) 
        return ; 
    this->ar[index] = val; 
} 

void delete_int_vector(struct IntVector *this) {
    free(this->ar); 
    free(this); 
}