
main.o: main.cpp
	g++ -std=c++14 -c $^ -o $@ -lglfw -lGL

program.out: main.o
	g++ -std=c++14 $^ -o $@ -lglfw -lGL

run: program.out
	./program.out
