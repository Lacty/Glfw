
program: main.o
	g++ -o program main.o -lglfw -lGL -lAntTweakBar -lX11

main.o: main.cpp
	g++ -std=c++11 -c -o main.o main.cpp -lglfw -lGL -lAntTweakBar -lX11

run: program
	./program
