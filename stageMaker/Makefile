
main    = debug/main.o
maker   = debug/maker.o
program = debug/program.out
objs    = $(main) $(maker)

libs    = -lglfw -lGL
cmpopt  = -Wall -std=c++14

$(program): $(objs)
	g++ $^ -o $@

$(main): src/main.cpp
	g++ $(cmpopt) $(libs) -c $^ -o $@

$(maker): src/maker/maker.cpp
	g++ $(compopt) $(libs) -c $^ -o $@

run: $(program)
	$^
