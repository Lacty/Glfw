
main   = debug/main.o
camera = debug/camera.o

program = debug/program.out
objs    = $(main) $(camera)

libs = -lglfw -lGL
opt  = -Wall -std=c++14

$(program): $(objs)
	g++ $(opt) $(libs) $^ -o $@

$(main): src/main.cpp
	g++ $(opt) $(libs) -c $^ -o $@

$(camera): src/camera.cpp
	g++ $(opt) $(libs) -c $^ -o $@

run: $(program)
	$^

clear: $(program) $(objs)
	rm $^
