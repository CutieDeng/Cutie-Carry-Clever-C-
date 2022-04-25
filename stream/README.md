# Stream Introduction

`stream` is obviously the core abstract model to deal with the sequence data. 

Whatever a list or an alphabetic string we can unify to the *sequence data* model. 

---

Let's shoot a quickly glance at this point. 

Firstly, we consider to realize a log system. We should use it to parse our different type data to a string. And it would help us to do more things well, especially when we need to debug our program. 

The first scenario we meet is a simple student management system: you need to print out the all students information! 
A student would contains some infomation: 
- name 
- unique identity code 
- borrowed book list 
- graduate information: the graduated year 

For example: 
{name: Cutie Deng, identity-code: 314159265, borrowed-books: (None), graduated-year: 2077} 

Let's have a try! 
