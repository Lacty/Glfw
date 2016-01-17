
main   = debug/main.o
native = debug/native.o

program = debug/program.out
objs    = $(main) $(native)

libs = -lglfw -lGL -lAntTweakBar -lX11
opt  = -Wall -std=c++14

$(program): $(objs)
	g++ $(opt) $(libs) $^ -o $@

$(main): src/main.cpp
	g++ $(opt) $(libs) -c $^ -o $@

$(native): src/appNative.cpp
	g++ $(opt) $(libs) -c $^ -o $@

run: $(program)
	$^
