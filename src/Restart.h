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
	void PrintRestartFile(int myRank, int randSeed, int index, double currS, Input &currInput, Trajectory &currTraj) const;
	
	
private:
	
	static int
	StringToInt(string a);
	void EraseFile(char* filename) const;
	
	// data members
		
	//config array, starts and 0 and goes to length^2
};

#endif /*_RESTART_H*/
