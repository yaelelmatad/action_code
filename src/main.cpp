#include <iostream>
#include <stdlib.h>
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<float.h>
#include<iostream>
#include<fstream>
#include<mpi.h>
using namespace std;
float pi = 3.14159265;

#include "Trajectory.h"
#include "Slice.h"
#include "Config.h"
#include "Dynamics.h"
#include "Input.h"

int main (int argc, char * const argv[]) {
    // insert code here...
	//dynamics test2 (test, 1.0, 1.0, true, 1.0, 1.0);
	//trajectory test3(2.0, 1.0, 10, 3, 3);

	int comm_sz;
	int my_rank;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);	
	
	Input runInput("inputFile");
	Config test(runInput);
	Trajectory trajectory(runInput, test);
	int fileIndicator = my_rank;
	//int fileIndicator = 1;
	trajectory.printTrajectory(fileIndicator);
	
	MPI_Finalize();

    return 0;


}

