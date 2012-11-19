/*
 *  restart.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 7/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

// Class header
#include "Restart.h"

// Other includes
#include "Input.h"
#include "Trajectory.h"
#include "TPS.h"

// Some of this is probably unnecessary
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <float.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

Restart::Restart()
{
	//empty constructor just sets this value for -1 which we can use as an indicator
	m_restartedCommSz = -1;
}

bool Restart::properlyRestarted(char* restartFile, int launched_comm_sz) 
{
	//actually stores the restartFile info
	FILE* in;
	in = fopen(restartFile, "r");
	fscanf(in, "%i \n", &m_restartedCommSz);

	fclose(in);  	
	if (m_restartedCommSz == launched_comm_sz)
	{
		return true;
	}
	else 
	{
		return false;
	}

}

int Restart::getOldCommSz() const
{
	if (m_restartedCommSz != -1)
		return m_restartedCommSz;
	else
	{
		cout << " Please call Restart::properlyRestarted(restartFile, launched_comm_sz before calling Restart::getOldCommSz!" << endl;
		return -1;
	}
}

int Restart::GetRandomSeed() const
{
	return m_randSeed;
}



int Restart::GetIndex() const
{
	return m_index;
}

void Restart::LoadRestart(Input & myInput, Trajectory &myTraj, TPS &myTPS, char* restartFile, int myRank, int comm_sz)
{
	sprintf( restartFile +strlen(restartFile), "_rank_%d.dat", myRank);
	cout <<"Restart File Name "  << restartFile << endl;
	
	FILE* fle1;
	fle1 = fopen(restartFile, "r");

	fscanf(fle1, "%i \n", &m_index);
	cout << "m_index " << m_index << endl;
	fscanf(fle1, "%i \n", &m_randSeed);
	cout << "m_randSeed " << m_randSeed << endl;
	fscanf(fle1, "%lf \n", &m_currS);	
	cout << "m_currS " << m_currS << endl;

	
	myTPS.SetS(m_currS);
	
	myTraj.LoadRestartTraj(fle1);
	
	fclose(fle1);
	
	
	
	return;
}

void Restart::PrintRestartFile(int myRank, int myCommSz, int randSeed, int index, double currS, Input &currInput, Trajectory &currTraj) const
{
	//store trajectory every StoreFrequency amount of trajecotry for restarts
	//line 1 = index of trajectory
	//line 2 = idum (random number genteartor seed)
	//next nSlices+1 lines = lattice of slices with each line representing one slice
	//next nSlices+1 lines = actionaccum array (1-4) 
	//[1]=Number of faciliated 0->1 flips
	//[2]=Number of fac 1->0 flips
	//[3]=Number of unfac 0->1 flips
	//[4]=Number of unfac 1->0 flips
	//next line is the numbers that go in plistsN[]
	//next 4 lines is the values that go in the arrays plists[][]
	//the next N lines are the backIndexes[][] values  
	if (myRank == 0)
	{
		char filename[1024];
		sprintf( (char*)filename, "Restart_index_%d", index );
		EraseFile(filename);
		//cout << filename << "\n";
		FILE * fle1;
		fle1 = fopen(filename, "a");
		fprintf(fle1, "%i \n", myCommSz);
		fclose(fle1);
	
	}
	
	char filename[1024];
	sprintf( (char*)filename, "Restart_index_%d_rank_%d.dat", index, myRank );
	EraseFile(filename);
	//cout << filename << "\n";
	FILE * fle1;
	fle1 = fopen(filename, "a");
	fprintf(fle1, "%i \n", index);
	fprintf(fle1, "%i \n", randSeed);
	fprintf(fle1, "%lf \n", currS);
	
	//cout << "curr S " << currS << endl;
	
	currTraj.PrintRestartTraj(fle1);
	fclose(fle1);
	return;
	 
}


void Restart::EraseFile( const char *fle) const
//erases file pointed to by fle.
{
	FILE * fle1;
	fle1 = fopen(fle, "w");
	fclose(fle1);
}





/*
int Restart::GetIntInput(int indicator) const
{
	return intParams[indicator];
}
 */
/*
double Restart::GetDoubleInput(int indicator) const
{
	return doubleParams[indicator];
}
*/
// static

/*
int Restart::StringToInt( const string& a)
{
	
	string sN_SITES_SUB ("N_SITES_SUB");
	
	/////////////////////////
	
	//this is a macro, passing it a string returns the enum
#define MATCH_STRING_TO_ENUM( __StringName__ ) \
else if( a.compare( #__StringName__ )==0){ return __StringName__; }
	
	//first one has the if statement (no macro)
	if (a.compare(sN_SITES_SUB)==0)
	{
		return N_SITES_SUB;
		
	}
	MATCH_STRING_TO_ENUM( N_SITES_FULL )
	MATCH_STRING_TO_ENUM( N_TRAJS )
	MATCH_STRING_TO_ENUM( N_SLICES )
	MATCH_STRING_TO_ENUM( N_SLICES_SHIFT )
	MATCH_STRING_TO_ENUM( N_STORAGEFREQ )
	MATCH_STRING_TO_ENUM( N_DIMENSION )
	MATCH_STRING_TO_ENUM( N_HARD )
	
	MATCH_STRING_TO_ENUM( D_TEMP )
	MATCH_STRING_TO_ENUM( D_DENSITY )
	MATCH_STRING_TO_ENUM( D_TOBS )
	MATCH_STRING_TO_ENUM( D_START_S )
	MATCH_STRING_TO_ENUM( D_END_S )
	MATCH_STRING_TO_ENUM( D_S_INC )
	MATCH_STRING_TO_ENUM( D_RATE_LEFT )
	MATCH_STRING_TO_ENUM( D_RATE_RIGHT )
	MATCH_STRING_TO_ENUM( D_U )
	MATCH_STRING_TO_ENUM( D_DIFF_RATE )
	MATCH_STRING_TO_ENUM( D_SHOOT_FRACTION )
	else 
	{
		cout << "INVALID INPUT" << endl;
		return -1;
	}
	
}
*/

