
program: main.o
	g++ -o program main.o -lglfw -lGL -Llib/libAntTweakBar.a

main.o: main.cpp
	g++ -std=c++11 -c -o main.o main.cpp -lglfw -lGL -Llib/libAntTweakBar.a

run: program
	./program
