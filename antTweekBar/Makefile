
program: main.o
	g++ -o program main.o -lglfw -lGL lib/libAntTweakBar.a -lX11

main.o: main.cpp
	g++ -std=c++11 -c -o main.o main.cpp -lglfw -lGL lib/libAntTweakBar.a -lX11

run: program
	./program
