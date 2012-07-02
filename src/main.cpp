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
#include "TPS.h"

int main (int argc, char * const argv[]) {

	int comm_sz;
	int my_rank;

	
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);	
	
	Direction direction = EDirection_FORWARD;
	
	srand(my_rank);
	Input runInput("inputFile", my_rank);
	Config test(runInput);

	Trajectory trajectory(runInput, direction);
	int fileIndicator = my_rank;
	
	trajectory.printTrajectory(fileIndicator);
	
	TPS myTPS(runInput, 0.02);
	for (int i = 1; i<= 200; i++)
	{
		cout << "traj index = " << i << endl;
		myTPS.TPS_move(trajectory);
		cout << endl;
		trajectory.printTrajectory(i);
	}
	 
	
	
	MPI_Finalize();

    return 0;


}

