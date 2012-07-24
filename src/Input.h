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

#include <string>
#include "Constants.h"

enum IntParameters
{
	N_SITES_SUB,
	N_SITES_FULL,
	N_TRAJS,
	N_TRAJS_EQUIL,
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
	D_DIFF_RATE,
	D_SHOOT_FRACTION
};

using namespace std;

class Input{
public:
	Input(); //overloaded const
    Input(const char* inputFile, int myRank); //overloaded constructor

	void    ReadInput( const char* inputFile, int myRank);
	int 	GetIntInput(int indicator) const; //you'll need to change this if you add parameters!
	double 	GetDoubleInput(int indicator) const;

private:

	static int	StringToInt( const std::string& a);
	
	// data members
	int 	intParams[MAXARGS];
	double 	doubleParams[MAXARGS];
	
		//friend class dynamics;

	//config array, starts and 0 and goes to length^2
};

#endif /*_INPUT_H*/
