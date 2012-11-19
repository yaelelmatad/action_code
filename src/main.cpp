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
#include "Restart.h"

int main (int argc, char * const argv[]) {

	int comm_sz;
	int my_rank;

	//sets up the MPI 
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);	

	//prints the number of processors
	cout << "comm_sz " << comm_sz << endl;

	
	char* inputFile;
	char* restartFile;
	Restart my_restart;
	int restartIndex = 0;
	//seeds the random number  generator depending on the rank of the process
	int seed = my_rank;
	srand(seed); 
	//so as to avoid overlapping seeds we then reseed with the first random number
	seed = rand();
	srand(seed);
	
	//set up input files
	Input runInput;
	
	//set up working trajectory
	Trajectory trajectory;
	bool restarted;
	Direction direction = EDirection_FORWARD;
	
	//set up trajectory dynamics
	TPS myTPS;
	
	if( argc == 3 ) {
		restarted = true; 		//this means we are restarting
		inputFile = argv[1];	//first argument is in put file
		restartFile = argv[2];	//second argument is restart file
		runInput.ReadInput(inputFile, my_rank); 		//read input parameters
		//set up a temp TPS and construct it and then copy it to myTPS
		TPS tempTPS(runInput, my_rank, comm_sz);
		myTPS=tempTPS;
		
		//check that restart run had same number of processors as this one was launched with
		if (!my_restart.properlyRestarted(restartFile, comm_sz))
		{
			cout << "Attempting to launch restart with wrong number of processors \n";
			cout << "Launched with " << comm_sz << " should have been launched with " << my_restart.getOldCommSz() << endl;
			return 1;
		}
		
		Trajectory temp_trajectory(runInput, direction); //construct an initial trajectory
		my_restart.LoadRestart(runInput, temp_trajectory, myTPS, restartFile, my_rank, comm_sz); //load the restart trajectory for this rank into it.
		seed = my_restart.GetRandomSeed(); //seed it from the old run seed
		restartIndex = my_restart.GetIndex(); //need the indexing correct for seeding
		cout << "restartIndex " << restartIndex << endl;
		trajectory = temp_trajectory; //copy this temporary trajectory into the real traj
		//cout << "myTPS CURR S " << myTPS.GetCurrS() << endl;
		my_restart.PrintRestartFile(my_rank, comm_sz, seed, 0, myTPS.GetCurrS(), runInput, trajectory); //print the "seed" traj back out 
		trajectory.PrintTrajectory(my_rank,0,myTPS.GetCurrS());
		trajectory.EraseOrderParameterFile(myTPS.GetCurrS());
    }
	else if (argc == 2)
	{
		restarted = false;
		inputFile = argv[1];
		//Input tempInput(inputFile, my_rank);
		runInput.ReadInput(inputFile, my_rank);
		TPS tempTPS(runInput, my_rank, comm_sz);
		myTPS=tempTPS;
		Trajectory seedtrajectory(runInput, direction);
		trajectory = seedtrajectory;
		trajectory.EraseOrderParameterFile(myTPS.GetCurrS());

	}
    else 
	{
		cout << "Usage (with Restart): ./action InputFile RestartFile\n";
		cout << "Using (without Restart): ./action InputFile\n"; 
		return 1;
    }
							   
	int m_n_traj = runInput.GetIntInput(N_TRAJS); //total number of trajectories to get
	int m_n_traj_equil = runInput.GetIntInput(N_TRAJS_EQUIL); //total number of equilibration trajectories to do
	int m_n_storagefreq = runInput.GetIntInput(N_STORAGEFREQ);	//storage frequency of restart trajs for checkpointing

	if (!restarted)
	{
		cout << "Not Restarted \n";
		for (int i = 0 ; i< m_n_traj_equil; i++) //equilibrate the seed trajectory if starting from scratch
		{
		//	cout << "Rank " << my_rank << " equilibration reached trajectory " << i << " of "<< m_n_traj_equil << endl;
			myTPS.TPS_move(trajectory);
			seed = seed++; //increment seed and then reseed to make sure that we can store the correct information
			//note that this seed in some sense is the seed for the NEXT trajectory
			srand(seed);
		}
		//store the final equilibrated trajectory
		my_restart.PrintRestartFile(my_rank, comm_sz, seed, 0, myTPS.GetCurrS(), runInput, trajectory);
		trajectory.PrintTrajectory(my_rank,0,myTPS.GetCurrS());
	}	
	else 
	{ //restarted
		cout << "Restarted \n";
		srand(seed);
	} 

	trajectory.PrintOrderParameter(myTPS.GetCurrS()); //print the 0th order paramter
    double tempS;
	//after equilibration or reloading 
	for (int i = 1; i<= m_n_traj; i++)
	{
		myTPS.TPS_move(trajectory); //actually does the TPS stuff
		trajectory.PrintOrderParameter(myTPS.GetCurrS()); //prints the order parameter
		seed++; //increments the seed
		srand(seed); //reseeds the rand num gen
		if (i%m_n_storagefreq == 0)  //prints a checkpoint/restart file every "m_n_storagefreq" amt
		{
			cout << "Rank " << my_rank << " reached trajectory " << i << " of "<< m_n_traj<< endl;
			trajectory.PrintTrajectory(my_rank,i,myTPS.GetCurrS()); //prints the trajs (for gnuplot printing)
			my_restart.PrintRestartFile(my_rank, comm_sz, seed, i, myTPS.GetCurrS(), runInput, trajectory); //prints the restart (for reloading into code)
		}
        
        double myCurrS[1];
        *myCurrS = (double)(myTPS.GetCurrS());
        if (my_rank == 0 || my_rank == 1){
            int recv_rank = abs(my_rank-1);
            MPI_Send(&myCurrS,1, MPI_DOUBLE, recv_rank, 0, MPI_COMM_WORLD);
        }
        if (my_rank == 0 || my_rank == 1){
            double*  temps;
            int recv_rank = abs(my_rank-1);
            MPI_Recv(&tempS,1, MPI_DOUBLE, recv_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            myTPS.SetS(tempS);
            cerr << "RANK " << my_rank << " recv " << tempS << endl;
        }
        
	}
	

	MPI_Finalize();
    return 0;


}

