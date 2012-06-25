/*
 *  trajectory.h
 *  
 *
 *  Created by Yael Elmatad on 8/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef _TRAJECTORY_H
#define	_TRAJECTORY_H
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

#define NSLICESMAX 5000
#define MAXSIZE 10000

#include "slice.h"
#include "input.h"

/*enum OccState
{
	OCCUPIED,
	UNOCCUPIED,
};*/

using namespace std;

class trajectory {
public:
    trajectory(); //overloaded const
    trajectory(input &myInput); //overloaded constructor
    virtual ~trajectory(); //destructor
	//some getters and setters
    //void setInfo(int _old, int _new,long currStep);

	//public variables
	//long int idum=-1; 
	
private:
	//functions
	//float ran2;
	//member variables
	//slice m_trajectory[NSLICESMAX];
	vector<slice> m_traj;
	double m_density;
	int m_length;
	double m_n_slices;
	//double m_J;
	//double m_temp;
	//config array, starts and 0 and goes to length^2
	
	friend class slice; 
};

#endif /*_TRAJECTORY_H*/