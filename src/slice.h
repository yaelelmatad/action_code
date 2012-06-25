/*
 *  slice.h
 *  Action
 *
 *  Created by Yael Elmatad on 8/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef _SLICE_H
#define	_SLICE_H
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
#include "dynamics.h"
#include "input.h"

#define MAXSIZE 10000
/*enum OccState
{
	OCCUPIED,
	UNOCCUPIED,
};*/

using namespace std;

class slice{
public:
    slice(); //overloaded const
	// slice( const config& );
    slice( input &, dynamics &, bool first ); //overloaded constructor
    virtual ~slice(); //destructor
	//some getters and setters
    //void setInfo(int _old, int _new,long currStep);
	//public variables
	//long int idum=-1; 
	
private:
	//functions
	//float ran2;
	//member variables
	double m_timeInterval;
	bool m_first;
	inline dynamics& m_dynamics() { return *p_curr_dynamics; }
	dynamics* p_curr_dynamics;	
	config m_firstConfig; //first is the one that is the last config in that slice TIME WISE (with earlier time)
	config m_lastConfig; //last is the last one in that slice TIME WISE

	friend class dynamics;

	//config array, starts and 0 and goes to length^2
};

#endif /*_SLICE_H*/
