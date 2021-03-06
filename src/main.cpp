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

#define MAX_COMM_SZ 1000


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
    int swapArray[MAX_COMM_SZ];
    
	//sets up the MPI 
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (1 == comm_sz%2)
    {
        if (0 == my_rank)
        {
           cout << "Attempting to launch with odd comm_sz, comm_sz must be even" << endl;
        }
        MPI_Finalize();
        return 1;
    }
    
    //MPI STUFF, THIS JUST SETS UP AN ARRAY
    //LATER WE WILL DO ARBITRARY IN THE ARRAY
    //THEN WE WILL SWAP ADJACENT VALS
    //ie, whatever in swapArray[0] swaps with whatever in swapArray[1], etc...

    
    
	//prints the number of processors
    if (my_rank == 0)
	{
        cout << "comm_sz is " << comm_sz << endl;

    }
	
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
            cout << "Possiblly attempting to launch with odd comm_sz, comm_sz must be even" << endl;
            MPI_Finalize();
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
        if (0==my_rank)
        {
            cout << "Usage (with Restart): ./action InputFile RestartFile\n";
            cout << "Using (without Restart): ./action InputFile\n";
		}
        MPI_Finalize();

        return 1;

    }
				
	int m_n_traj = runInput.GetIntInput(N_TRAJS); //total number of trajectories to get
	int m_n_traj_equil = runInput.GetIntInput(N_TRAJS_EQUIL); //total number of equilibration trajectories to do
	int m_n_storagefreq = runInput.GetIntInput(N_STORAGEFREQ);	//storage frequency of restart trajs for checkpointing
    int n_swap_freq = runInput.GetIntInput(N_SWAPFREQ);
    int n_swap_array_swaps_per_cycle = comm_sz*runInput.GetIntInput(N_NUMSWAPS_DIV_BY_COMM_SZ);
    
	if (!restarted)
	{
        if (0 == my_rank){
            cout << "Not Restarted \n";
		}
        
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
		if (0 == my_rank){
            cout << "Restarted \n";
		}
        srand(seed);
	} 

	trajectory.PrintOrderParameter(myTPS.GetCurrS()); //print the 0th order paramter
    double tempS;
	//after equilibration or reloading 
	for (int i = 1; i<= m_n_traj; i++)
	{
		myTPS.TPS_move(trajectory); //actually does the TPS stuff
		trajectory.PrintOrderParameter(myTPS.GetCurrS()); //prints the order parameter
        
        /***********************MPI*************************/

        if (0==i%n_swap_freq)
        {
            
            if (0==my_rank)
            {
                cout << "swap attempt on traj " << i << endl;
                //shuffle the swapArray
                //NOTE: YOU MUST MAKE SURE YOU SAVE AND RELOAD THIS INFORMATION FOR NEXT TIME YOU RUN THE SIMULATION
                int firstSwap;
                int secondSwap;
                int temp;
                
                //set up the swap matrix  (redo each time to avoid having to save state of swap array in restart files)
                for (int i=0; i<MAX_COMM_SZ;i++)
                {
                    swapArray[i]=i;
                }
                
                //arbitrarily swap lots of times so you shuffle the array
                for (int i = 0; i<n_swap_array_swaps_per_cycle; i++)
                {
                    firstSwap = rand()%comm_sz;
                    secondSwap = rand()%comm_sz;
                    
                    temp = swapArray[firstSwap];
                    swapArray[firstSwap]=swapArray[secondSwap];
                    swapArray[secondSwap]=temp;
                }
                
                //determines who attempst to swap with whom.
                for (int i = 0; i < comm_sz; i=i+2)
                {
                    //send child/slave information for later swapping (only parent proc will handle decision making)
                    int child[1];
                    *child = 1;
                    int parent[1];
                    *parent = 0;
                    
                    //cout << swapArray[i] << " swaps with " << swapArray[i+1] << endl;
                    //cout << swapArray[i+1] << " swaps with " << swapArray[i] << endl;
                    
                    //temp stuff for stupid mpi
                    int swappers[1];
                    
                    //send the swapping information to all the nodes
                    
                    //send to the children (odd)
                    *swappers = swapArray[i];
                    MPI_Send(&swappers,1, MPI_INT, swapArray[i+1], 0, MPI_COMM_WORLD);
                    MPI_Send(&child,1, MPI_INT, swapArray[i+1], 1, MPI_COMM_WORLD);
                    
                    //send to parents (even)
                    *swappers = swapArray[i+1];
                    MPI_Send(&swappers,1, MPI_INT, swapArray[i], 0, MPI_COMM_WORLD);
                    MPI_Send(&parent,1, MPI_INT, swapArray[i], 1, MPI_COMM_WORLD);
                    
                    
                }
            }
            
            //wait until all trajectories have gotten this far before waiting for information (mostly for printing purposes)
            MPI_Barrier(MPI_COMM_WORLD);
            
            //recv your swap partner
            int mySwapper;
            int head_rank = 0;
            MPI_Recv(&mySwapper,1, MPI_INT, head_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //cout << "Rank " << my_rank << " recv swapper " << (mySwapper) << endl;
            
            //recv your parent child status
            int parent_or_child;
            MPI_Recv(&parent_or_child,1, MPI_INT, head_rank, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //cout << "Rank " << my_rank << " parent_or_child " << parent_or_child   <<endl;
            //wait until all trajectories have finished this traj before continuing and trying to do the swaps.
            
            //lets wait for good measure
            MPI_Barrier(MPI_COMM_WORLD);
            
            //there are two kind of processes, children and parents.  children send info to parents
            //parents actually compute rejection prob
            //parents return the value of field to child (which may be same as original field!)
            
            if (parent_or_child == 1) //child
            {
                //send your info to the parent
                double myK[1];
                *myK = (double)trajectory.GetOrderParameter();
                MPI_Send(&myK,1, MPI_DOUBLE, mySwapper, 2, MPI_COMM_WORLD);
                
                double myS[1];
                *myS = (myTPS.GetCurrS());
                MPI_Send(&myS,1, MPI_DOUBLE, mySwapper, 3, MPI_COMM_WORLD);
                //cout << my_rank << " sent to " << mySwapper << " K = " << *myK << " S = " << *myS << endl;
                
                
                //wait for your new value of S (might be your current value!)
                double swapS;
                MPI_Recv(&swapS,1, MPI_DOUBLE, mySwapper, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                myTPS.SetS(swapS);
                //cout << "my_rank " << my_rank << " current S " << swapS << endl;
                
                
            }
            
            if(parent_or_child == 0) //parent
            {
                //wait for information from child
                double swapK;
                double swapS;
                MPI_Recv(&swapK,1, MPI_DOUBLE, mySwapper, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&swapS,1, MPI_DOUBLE, mySwapper, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                //cout << my_rank << " recv from " << mySwapper << " K = " << swapK << " S = " << swapS << endl;
                
                //do some metropolis stuff
                double deltaK = (double)trajectory.GetOrderParameter()-swapK;
                double deltaS = myTPS.GetCurrS() - swapS;
                //cout << "deltaK " << deltaK << " delta S " << deltaS << endl;
                
                double boltz = exp(deltaK*deltaS);
                //cout << "botlz " << boltz << endl;
                //cout << "my_rank " << my_rank << " original S " << myTPS.GetCurrS() << endl;
                
                double randNum = ((double)rand()/(double)RAND_MAX);
                //cout << "botlz " << boltz << " rand num " << randNum << endl;
                if (randNum < boltz) //randnum guarantteed to be less than 1
                { //accept
                    double myS[1];
                    *myS = (myTPS.GetCurrS());
                    MPI_Send(&myS,1, MPI_DOUBLE, mySwapper, 4, MPI_COMM_WORLD);
                    myTPS.SetS(swapS); //change my S to the swap value of S
                    
                }
                else
                {  //reject
                    //send back the original value of S.
                    double originalS[1];
                    *originalS = swapS;
                    MPI_Send(&originalS,1, MPI_DOUBLE, mySwapper, 4, MPI_COMM_WORLD);
                }
                
                //cout << "my_rank " << my_rank << " current S " << (myTPS.GetCurrS()) << endl;
                
            }
        }
        /***********************MPI*************************/
        
        //this stuff must go after the MPI stuff to preserve the seeds properly, otherwise gets totally messed up.  
		seed++;//increments the seed
		srand(seed); //reseeds the rand num gen
		if (i%m_n_storagefreq == 0)  //prints a checkpoint/restart file every "m_n_storagefreq" amt
		{
			cout << "Rank " << my_rank << " reached trajectory " << i << " of "<< m_n_traj<< endl;
			trajectory.PrintTrajectory(my_rank,i,myTPS.GetCurrS()); //prints the trajs (for gnuplot printing)
			my_restart.PrintRestartFile(my_rank, comm_sz, seed, i, myTPS.GetCurrS(), runInput, trajectory); //prints the restart (for reloading into code)
		}
        
        
	}
	

	MPI_Finalize();
    return 0;


}

