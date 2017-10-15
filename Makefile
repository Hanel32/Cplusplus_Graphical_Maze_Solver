all: Main

Main: Adjacency_List.h Adjacency_Driver.cpp
	g++ -std=c++11 Adjacency_List.h Adjacency_Driver.cpp -o Main
clean:
	rm *.o Main
