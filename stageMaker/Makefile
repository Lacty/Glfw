
main   = debug/main.o
native = debug/native.o
camera = debug/camera.o
maker  = debug/maker.o

program = debug/program.out
objs    = $(main) $(native) $(camera) $(maker)

libs = -lglfw -lGL -lAntTweakBar -lX11
opt  = -Wall -std=c++14

$(program): $(objs)
	g++ $(opt) $(libs) $^ -o $@

$(main): src/main.cpp
	g++ $(opt) $(libs) -c $^ -o $@

$(native): src/appNative.cpp
	g++ $(opt) $(libs) -c $^ -o $@

$(camera): src/camera.cpp
	g++ $(opt) $(libs) -c $^ -o $@

$(maker): src/maker.cpp
	g++ $(opt) $(libs) -c $^ -o $@

run: $(program)
	$^
