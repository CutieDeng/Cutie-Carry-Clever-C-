# Why **Vector**? 

You can click this [link](https://en.cppreference.com/w/cpp/container/vector) to have a better understanding of `std::vector`. 

**The total content in this document is based on this reference and some experiments.** 

## preface 

As you know that, *array* is almost the most frequently-used data type in *c*. The reason is obviously that it gives the developers the strong abilities to master a group of elements without a loss in performance. 

At the same time, this strong ability must be used with a limitation of the amount of the elements. You must have to declare the length of the array you want to use and follow the rule that: *you only visits and changes the element in this array appropriately*. 

However, as a common human, a most inevitable thing is that violating an appointment or forgetting the constraints. For performance reasons, program language **C** doesn't give a compulsively security examination for this mistake in *runtime*. Same as **c plus plus**. 

## Definition 

Rather than the primordial array definition in C, which has been directly supported by an exclusive language grammar, *vector* seems more ordinary caused by the definition in header file *vector*. 

Just use the macro include statement and you can directly use this class to describe any array-like thing: `#include <vector>`. 

Since now, Thu May 19, 2022, the declaration of *vector* is like below: 
```C++
template <class T, class Allocator = std::allocator<T>> class vector; 
``` 

According to this definition, it's obviously simple within just two class type template arguments. 

Please note that, ***since C++17, a new definition is given using a overload method like below***: 
``` C++ 
namespace pmr {
    template <class T> 
    using vector = std::vector<T, std::pmr::polymorphic_allocator<T>>; 
}
``` 

Now we have no need to talk about the lib *memory_resource* to bring more complexity in our theme. Be at ease that we would smoothly take `polymorphic_allocator` class in consideration in the near future. 

As in the preface we have talked about, the *vector* container, sometimes regarded as an collection, is a type of encapsulation. 

Actually, it's not a difficult achievement, as we all know. To express this clearly, let's get hands dirty to design a basic and naive achievement for `vector`. 

## Naive Practice for Int Type Vector 

Firstly, we just consider the most easy situation: an vector is only supported with `int` type. 

It gives two picecs of convenience for us to do more things: 

1. The `int` type is a basic type. It only occupies four bytes physically and, in the abstract layer, it's a **strong ordering** type. You can ensure obviously that, the literal value gotten from it is the entire entity. If the codes `int x = 21, y = 21;`, you forever can not use the bool expression `x == y` but get `false` in this case. 

1. Similarly, `int` type only describes the data in 4 bytes (word). It's quite small then we can moves the value in the memory room safely! 

To make fully use of this characters, we clearly define it with three members: *element number*, *array length* and the *array pointer*. 

*Someone may put forward a question: Could we just use only two members of it, to shorten this dynamic array length?* 

The correct answer is that, of course you can. However, owing to the array pointer is **unavoidable** if we insist the principle of OO (Object-Oriented). 

*However, if you are willing to use a global data structure to do an information distribution, according to the boundary and extreme situation, you can even shorten this structure in 4 bytes if the upbound is allowed.* 

> But everything is a trade-off.

The excessive reduction of memory cost, would absolutely take complex situations in multi-thread context, when using a *static life cycle variable*. `Mutex` would be introduced in this framework to keep the security and correctness of the program, bringing about a performance loss. 

The second shortcoming is also similar, a complex data storage would be used to make the understanding hard. It's not just the adverse conditions for us to understand, also the additional temporal cost for our computing advices. 

Above all, we must balance the cost of encoding and decoding, considering the specific situations and give our results. 

Now let's focus on the simple situation, everything is normal and we actually do not meet any upper limit. 

Then we can simple define this `vector` : 

```c 
struct IntVector; 
``` 

*No interface, no c language.*

It's easy to define some related interface functions: 

```c
/** 
 * Push the value to the end of this vector! 
 */ 
void push_back(struct IntVector *, int ); 

/** 
 * Pop the value of the end of the vector. 
 */ 
void pop_back(struct IntVector *); 

/** 
 * Get the value using the index. 
 */ 
int at(struct IntVector *, size_t ); 

/** 
 * Remove the specific value according to the index. 
 */ 
void remove(struct IntVector *, size_t ); 

/** 
 * Get the size of the vector. 
 */ 
size_t size(struct IntVector *); 

/** 
 * Get the first element of vector. 
 */ 
int begin(struct IntVector *); 

/** 
 * Get the last element of vector. 
 */ 
int end(struct IntVector *); 
``` 

Let's give a simple [realization](./Vector1.h) of it. 