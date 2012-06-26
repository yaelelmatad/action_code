#account.make
# example working make file for use of the class Action
# files: source files:  main.cpp, Config.cpp, Slice.cpp, Trajectory.cpp, Input.cpp
#        header file:  Config.h, Slice.h, Trajectory.h, Input.h
# executable file: action
#

# first define target file : action
#              dependencies are the object files that build the program

action: build/main.o build/Config.o build/Slice.o build/Trajectory.o build/Dynamics.o build/Input.o
#action: main.o Config.o Slice.o Trajectory.o Input.o
	g++ -o action build/main.o build/Config.o build/Slice.o build/Trajectory.o build/Dynamics.o build/Input.o

# now define how each object file is a target and list dependencies and how
#  to build that object file if any dependencies change

build/main.o: src/main.cpp
	g++ -c src/main.cpp -o build/main.o

build/Dynamics.o: src/Dynamics.cpp src/Dynamics.h
	g++ -c src/Dynamics.cpp -o build/Dynamics.o

build/Config.o: src/Config.cpp src/Config.h
	g++ -c src/Config.cpp -o build/Config.o

build/Slice.o: src/Slice.cpp src/Slice.h
	g++ -c src/Slice.cpp -o build/Slice.o

build/Trajectory.o: src/Trajectory.cpp src/Trajectory.h
	g++ -c src/Trajectory.cpp -o build/Trajectory.o

build/Input.o: src/Input.cpp src/Input.h
	g++ -c src/Input.cpp -o build/Input.o

clean:
	rm action build/main.o build/Config.o build/Slice.o build/Trajectory.o build/Input.o build/Dynamics.o

# that's all


