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

#define MAXSIZE 10000
/*enum OccState
{
	OCCUPIED,
	UNOCCUPIED,
};*/

using namespace std;

class slice{
public:
    //slice(); //overloaded const
    slice(config(), double, double, bool, double ); //overloaded constructor
    virtual ~slice(); //destructor
	//some getters and setters
    //void setInfo(int _old, int _new,long currStep);
	//public variables
	//long int idum=-1; 
	
private:
	//functions
	//float ran2;
	//member variables
	double m_temp;
	double m_deltaT;
	config m_config(); //this is the first config of the slice, in the case of back shooting, make sure to overwrite this with the final config.  
	double m_J ;
	double m_dir; 
	//config array, starts and 0 and goes to length^2
};

#endif /*_SLICE_H*/
