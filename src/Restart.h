/*
 *  restart.h
 *  Action
 *
 *  Created by Yael Elmatad on 7/2012
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef _RESTART_H
#define	_RESTART_H
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <float.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

//#include "Config.h"
//#include "Dynamics.h"

#include "Input.h"
#include "Trajectory.h"
#include "TPS.h"

#define MAXARGS 100
/*
enum IntParameters
{
	N_SITES_SUB,
	N_SITES_FULL,
	N_TRAJS,
	N_SLICES,
	N_SLICES_SHIFT,
	N_STORAGEFREQ,
	N_DIMENSION,
	N_HARD
};
*/
using namespace std;

class Restart{
public:
	Restart(); //overloaded const
	void PrintRestartFile(int myRank, int myCommSz, int randSeed, int index, double currS, Input &currInput, Trajectory &currTraj) const;
	bool properlyRestarted(char* restartFile, int launched_comm_sz) ;
	int getOldCommSz() const;
	int GetIndex() const;
	void LoadRestart(Input & myInput, Trajectory &myTraj, TPS &myTPS, char* restartFile, int my_rank, int comm_sz);
	
	int m_restartedCommSz;
	
private:
	
	static int
	StringToInt(string a);
	void EraseFile(char* filename) const;
	int m_randSeed;
	int m_index;
	double m_currS;
	
	// data members
		
	//config array, starts and 0 and goes to length^2
};

#endif /*_RESTART_H*/
