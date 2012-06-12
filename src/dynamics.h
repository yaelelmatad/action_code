/*
 *  slice.h
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

#include "config.h"

#define MAXSIZE 10000
enum OccState
{
	OCCUPIED,
	UNOCCUPIED,
};


using namespace std;

class dynamics{
public:
    //slice(); //overloaded const
    dynamics( config &, double, double, double, double ); //overloaded constructor
    virtual ~dynamics(); //destructor
	//some getters and setters
    //void setInfo(int _old, int _new,long currStep);
	//public variables
	//long int idum=-1; 
	
private:
	//functions
	//float ran2;
	//member variables
	
	inline config& m_config() { return *p_curr_config; }
	
	double m_temp;
	double m_cprob; //exp(-1/T)
	double m_epsilon;
	double m_leftRate;
	double m_rightRate;
	double m_totalRate;
	double m_rates[NUM_LISTS]; //keeps individual rates for easy updating (for one of such process)
	config* p_curr_config; 	
	void m_pickAndFlipSpin();
	double m_pickATime();
	void m_setTotalRate();
	double m_updateTransRate();

	friend class config;
};

#endif /*_SLICE_H*/
