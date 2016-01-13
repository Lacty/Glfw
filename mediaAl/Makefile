
program: main.o
	g++ -o program main.o -lglfw -lGL -lopenal

main.o: main.cpp
	g++ -std=c++14 -Wall -c -o main.o main.cpp -lglfw -lGL -lopenal

run: program
	./program
