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

	
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);	

	cout << "comm_sz " << comm_sz << endl;

	char* inputFile;
	char* restartFile;
	Restart my_restart;
	int restartIndex = 0;
	int seed = my_rank;
	srand(seed); 
	seed = rand();
	Input runInput;
	Trajectory trajectory;
	bool restarted;
	Direction direction = EDirection_FORWARD;
	
	if( argc == 3 ) {
		inputFile = argv[1];
		restartFile = argv[2];
		runInput.ReadInput(inputFile, my_rank);
		restarted = true;
		//Trajectory my_trajectory(runInput, direction);
		//Trajectory trajectory = my_restart.LoadRestartFile(restartFile, my_rank);
		//restartIndex = my_restart.getRestartIndex();
		//seed = my_restart.getSeed();
    }
	if (argc == 2)
	{
		restarted = false;
		inputFile = argv[1];
		Input tempInput(inputFile, my_rank);
		runInput.ReadInput(inputFile, my_rank);
		Trajectory seedtrajectory(runInput, direction);
		trajectory = seedtrajectory;
	}
    else 
	{
		cout << "Usage (with Restart): ./action InputFile RestartFile\n";
		cout << "Using (without Restart): ./action InputFile\n"; 
		return 1;
    }
	double start_s = runInput.GetDoubleInput(D_START_S);
	double end_s = runInput.GetDoubleInput(D_END_S);
	
	double currS;
	
	if (end_s > start_s)
	{	double range = end_s - start_s;
		double increment = range/(comm_sz-1);
		currS = start_s + increment*my_rank;
	}
	else {
		double range = start_s - end_s;
		double increment = range/(comm_sz-1);
		currS = start_s - increment*my_rank;
	}
	
	cout << "S = " << currS << " on rank " << my_rank << endl;

	
	int m_n_traj = runInput.GetIntInput(N_TRAJS);
	int m_n_traj_equil = runInput.GetIntInput(N_TRAJS_EQUIL);
	int m_n_storagefreq = runInput.GetIntInput(N_STORAGEFREQ);	
	
	TPS myTPS(runInput, currS);

	if (!restarted)
	{
		cout << "Not Restarted \n";
		srand(seed);
		for (int i = 0 ; i< m_n_traj_equil; i++)
		{
			//trajectory.printTrajectory(i);
			//cout << "traj index = " << i << endl;
			myTPS.TPS_move(trajectory);
			cout << endl;
			seed = seed + i;
			srand(seed);
			//my_restart.PrintRestartFile(my_rank, seed, i, currS, runInput, trajectory);
		}
		
		trajectory.printTrajectory(my_rank,0,currS);
		for (int i = 1; i <= m_n_traj; i++)
		{
			cout << "traj index = " << i << endl;
			myTPS.TPS_move(trajectory);
			cout << endl;
			seed = seed + i;
			srand(seed);
			if (i%m_n_storagefreq == 0)
			{
				cout << "Rank " << my_rank << " reached trajectory " << i << " of "<< m_n_traj<< endl;
				trajectory.printTrajectory(my_rank,i,currS);
				my_restart.PrintRestartFile(my_rank, seed, i, currS, runInput, trajectory);
			}
		}
	}	
	else 
	{ //restarted
		cout << "Restarted \n";
		srand(seed);
		seed = seed + m_n_storagefreq;
		trajectory.printTrajectory(my_rank,0,currS);
		for (int i = 1; i<= m_n_traj; i++)
		{
			cout << "traj index = " << i << endl;
			myTPS.TPS_move(trajectory);
			cout << endl;
			seed = seed + i;
			srand(seed);
			if (i%m_n_storagefreq == 0)
			{
				cout << "Rank " << my_rank << " reached trajectory " << i << " of "<< m_n_traj<< endl;
				trajectory.printTrajectory(my_rank,i,currS);
				my_restart.PrintRestartFile(my_rank, seed, i, currS, runInput, trajectory);
			}
		}
	} 
	
	
	MPI_Finalize();

    return 0;


}

