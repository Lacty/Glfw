
main = debug/main.o

program = debug/program.out
objs    = $(main)

opt = -Wall -std=c++14

$(program): $(objs)
	g++ $(opt) $^ -o $@

$(main): src/main.cpp
	g++ $(opt) -c $^ -o $@

run: $(program)
	$^
