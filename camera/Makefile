
program: main.o
	g++ -o program main.o -lglfw -lGL

main.o: main.cpp
	g++ -std=c++14 -Wall -c -o main.o main.cpp -L /usr/local/bin/ -lglfw -lGL

run: program
	./program
