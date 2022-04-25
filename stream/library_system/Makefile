cc = g++ -std=c++17

main: demo.o student_info.o 
	$(cc) demo.o student_info.o -o $@

demo.o student_info.o:%.o:%.cpp
	$(cc) -c $< -o $@	

.PHONY: clean run 

clean: 
	-rm *.o main

run: main 
	@./main