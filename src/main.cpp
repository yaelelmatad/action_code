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
	srand(seed);
	Input runInput;
	Trajectory trajectory;
	bool restarted;
	Direction direction = EDirection_FORWARD;
	TPS myTPS;
	
	if( argc == 3 ) {
		inputFile = argv[1];
		restartFile = argv[2];
		runInput.ReadInput(inputFile, my_rank);
		TPS tempTPS(runInput, my_rank, comm_sz);
		myTPS=tempTPS;
		restarted = true;
		if (!my_restart.properlyRestarted(restartFile, comm_sz))
		{
			cout << "Attempting to launch restart with wrong number of processors \n";
			cout << "Launched with " << comm_sz << " should have been launched with " << my_restart.getOldCommSz() << endl;
			return 1;
		}
		Trajectory temp_trajectory(runInput, direction);
		my_restart.LoadRestart(runInput, temp_trajectory, myTPS, restartFile, my_rank, comm_sz);
		restartIndex = my_restart.GetIndex();
		trajectory = temp_trajectory;
		my_restart.PrintRestartFile(my_rank, comm_sz, seed, 555, myTPS.GetCurrS(), runInput, trajectory);
		trajectory.printTrajectory(my_rank,0,myTPS.GetCurrS());
		
		//restartIndex = my_restart.getRestartIndex();
		//seed = my_restart.getSeed();
    }
	else if (argc == 2)
	{
		restarted = false;
		inputFile = argv[1];
		Input tempInput(inputFile, my_rank);
		runInput.ReadInput(inputFile, my_rank);
		TPS tempTPS(runInput, my_rank, comm_sz);
		myTPS=tempTPS;
		Trajectory seedtrajectory(runInput, direction);
	//	seedtrajectory.printTrajectory(my_rank,0,myTPS.GetCurrS());
		//cout << "HERE???" << endl;
		trajectory = seedtrajectory;
	}
    else 
	{
		cout << "Usage (with Restart): ./action InputFile RestartFile\n";
		cout << "Using (without Restart): ./action InputFile\n"; 
		return 1;
    }
	
							   
	int m_n_traj = runInput.GetIntInput(N_TRAJS);
	int m_n_traj_equil = runInput.GetIntInput(N_TRAJS_EQUIL);
	int m_n_storagefreq = runInput.GetIntInput(N_STORAGEFREQ);	

	if (!restarted)
	{
		cout << "Not Restarted \n";
		for (int i = 0 ; i< m_n_traj_equil; i++)
		{
			//trajectory.printTrajectory(i);
			//cout << "traj index = " << i << endl;
			myTPS.TPS_move(trajectory);
			//cout << endl;
			seed = seed + i;
			srand(seed);
			//my_restart.PrintRestartFile(my_rank, seed, i, currS, runInput, trajectory);
		}
		
		my_restart.PrintRestartFile(my_rank, comm_sz, seed, 0, myTPS.GetCurrS(), runInput, trajectory);
		trajectory.printTrajectory(my_rank,0,myTPS.GetCurrS());

		for (int i = 1; i <= m_n_traj; i++)
		{
			//cout << "traj index = " << i << endl;
			myTPS.TPS_move(trajectory);
			//cout << endl;
			seed = seed + i;
			srand(seed);
			if (i%m_n_storagefreq == 0)
			{
				cout << "Rank " << my_rank << " reached trajectory " << i << " of "<< m_n_traj<< endl;
				my_restart.PrintRestartFile(my_rank, comm_sz, seed, i, myTPS.GetCurrS(), runInput, trajectory);
				trajectory.printTrajectory(my_rank,i,myTPS.GetCurrS());
			}
		}
	}	
	else 
		
		
	/*	
	{ //restarted
		cout << "Restarted \n";
		srand(seed);
		seed = seed +  restartIndex ;
		//trajectory.printTrajectory(my_rank,0,myTPS.GetCurrS());
		//my_restart.PrintRestartFile(my_rank, comm_sz, seed, 0, myTPS.GetCurrS(), runInput, trajectory);
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
				trajectory.printTrajectory(my_rank,i,myTPS.GetCurrS());
				my_restart.PrintRestartFile(my_rank, comm_sz, seed, i, myTPS.GetCurrS(), runInput, trajectory);
			}
		}
	} 
	*/
	
	MPI_Finalize();

    return 0;


}

