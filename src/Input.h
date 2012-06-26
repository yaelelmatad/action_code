/*
 *  input.h
 *  Action
 *
 *  Created by Yael Elmatad on 6/25/2012
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef _INPUT_H
#define	_INPUT_H
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

#define MAXARGS 100

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

enum DoubleParameters
{
	D_TEMP,
	D_DENSITY,
	D_TOBS,
	D_START_S,
	D_END_S,	
	D_S_INC,
	D_RATE_LEFT,
	D_RATE_RIGHT,
	D_U,
	D_DIFF_RATE
};

using namespace std;

class Input{
public:
   // input(); //overloaded const
    Input(char* inputFile, int myRank); //overloaded constructor
	int getIntInput(int indicator); //you'll need to change this if you add parameters!
	double getDoubleInput(int indicator);
	int stringToInt(string a);

    virtual ~Input(); //destructor
	//some getters and setters
    //void setInfo(int _old, int _new,long currStep);
	//public variables
	//long int idum=-1; 
	
private:
	int intParams[MAXARGS];
	double doubleParams[MAXARGS];
	
		//friend class dynamics;

	//config array, starts and 0 and goes to length^2
};

#endif /*_INPUT_H*/
