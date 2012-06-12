#account.make
# example working make file for use of the class Action
# files: source files:  main.cpp, config.cpp, slice.cpp, trajectory.cpp
#        header file:  config.h, slice.h, trajectory.h
# executable file: action
#

# first define target file : action
#              dependencies are the object files that build the program

action: build/main.o build/config.o build/slice.o build/trajectory.o build/dynamics.o
#action: main.o config.o slice.o trajectory.o
	g++ -o action build/main.o build/config.o build/slice.o build/trajectory.o build/dynamics.o

# now define how each object file is a target and list dependencies and how
#  to build that object file if any dependencies change

build/main.o: src/main.cpp
	g++ -c src/main.cpp -o build/main.o

build/dynamics.o: src/dynamics.cpp src/dynamics.h
	g++ -c src/dynamics.cpp -o build/dynamics.o

build/config.o: src/config.cpp src/config.h
	g++ -c src/config.cpp -o build/config.o

build/slice.o: src/slice.cpp src/slice.h
	g++ -c src/slice.cpp -o build/slice.o

build/trajectory.o: src/trajectory.cpp src/trajectory.h
	g++ -c src/trajectory.cpp -o build/trajectory.o

clean:
	rm action build/main.o build/config.o build/slice.o build/trajectory.o build/dynamics.o

# that's all


