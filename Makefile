#account.make
# example working make file for use of the class Action
# files: source files:  main.cpp, Config.cpp, Slice.cpp, Trajectory.cpp, Input.cpp, TPS.cpp, Restart.cpp
#        header file:  Constants.h, Config.h, Slice.h, Trajectory.h, Input.h, TPS.h, Restart.h
# executable file: action
#

# first define target file : action
#              dependencies are the object files that build the program

action: build/main.o build/Config.o build/Slice.o build/Trajectory.o build/Dynamics.o build/Input.o build/Restart.o build/TPS.o
#action: main.o Config.o Slice.o Trajectory.o Input.o TPS.o
	mpic++ -o action build/main.o build/Config.o build/Slice.o build/Trajectory.o build/Dynamics.o build/Input.o build/Restart.o build/TPS.o

# now define how each object file is a target and list dependencies and how
#  to build that object file if any dependencies change

build/main.o: src/main.cpp src/Constants.h
	mpic++ -c src/main.cpp -o build/main.o

build/Dynamics.o: src/Dynamics.cpp src/Dynamics.h
	mpic++ -c src/Dynamics.cpp -o build/Dynamics.o

build/Config.o: src/Config.cpp src/Config.h
	mpic++ -c src/Config.cpp -o build/Config.o

build/Slice.o: src/Slice.cpp src/Slice.h
	mpic++ -c src/Slice.cpp -o build/Slice.o

build/Trajectory.o: src/Trajectory.cpp src/Trajectory.h
	mpic++ -c src/Trajectory.cpp -o build/Trajectory.o

build/Input.o: src/Input.cpp src/Input.h
	mpic++ -c src/Input.cpp -o build/Input.o

build/Restart.o: src/Restart.cpp src/Restart.h
	mpic++ -c src/Restart.cpp -o build/Restart.o

build/TPS.o: src/TPS.cpp src/TPS.h
	mpic++ -c src/TPS.cpp -o build/TPS.o

clean:
	rm action build/main.o build/Config.o build/Slice.o build/Trajectory.o build/Input.o build/Restart.o build/Dynamics.o build/TPS.o

# that's all

