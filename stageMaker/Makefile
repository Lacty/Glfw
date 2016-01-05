
main    = debug/main.o
maker   = debug/maker.o
window  = debug/window.o
camera  = debug/camera.o
utility = debug/utility.o

program = debug/program.out
objs    = $(main) $(maker) $(window) $(camera) $(utility)

libs    = -lglfw -lGL -lftgl
cmpopt  = -Wall -std=c++14

$(program): $(objs)
	g++ $(cmpopt) $(libs) $^ -o $@

$(main): src/main.cpp
	g++ $(cmpopt) $(libs) -c $^ -o $@

$(maker): src/maker/maker.cpp
	g++ $(cmpopt) $(libs) -c $^ -o $@

$(window): src/window/window.cpp
	g++ $(cmpopt) $(libs) -c $^ -o $@

$(camera): src/camera/camera.cpp
	g++ $(cmpopt) $(libs) -c $^ -o $@

$(utility): src/utility/utility.cpp
	g++ $(cmpopt) $(libs) -c $^ -o $@

run: $(program)
	$^
