/*
 *  dynamics.h
 *  Action
 *
 *  Created by Yael Elmatad on 6/11/12.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef _DYNAMICS_H
#define	_DYNAMICS_H
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

#include "Config.h"
#include "Input.h"

#define MAXSIZE 10000
/*enum OccState
{
	OCCUPIED,
	UNOCCUPIED,
};
*/

using namespace std;

class Dynamics{
public:

    Dynamics( const Input &); //overloaded constructor
	
	void	UpdateConfig( Config*, double interval ) const;
	
private:
	
	void 	PickAndFlipSpin( Config& toUpdate, double totalRate ) const;

	void 	InitializeRates();

	double 	GetTotalRate( const Config& localConfig ) const;
	
	
	
	double m_temp;
	double m_cprob; //exp(-1/T)
	double m_epsilon;
	double m_leftRate;
	double m_rightRate;
	double m_rates[NUM_LISTS]; //keeps individual rates for easy updating (for one of such process)

	//void m_advanceDynamics(double);
	// to be called by other classes (slice?) to advance dynamics
	double m_pickATime( double totalRate ) const;
	
	friend class Slice;
	friend class Config;
};

#endif /*_SLICE_H*/
