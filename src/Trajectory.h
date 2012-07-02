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
#include <deque>
#include <iterator>
#include <string>
#include <sstream>

#define NSLICESMAX 5000
#define MAXSIZE 10000

#include "Slice.h"
#include "Input.h"

/*enum OccState
{
	OCCUPIED,
	UNOCCUPIED,
};*/

enum Side{
	ESide_BEGIN = -1,
	ESide_END = 1
};

using namespace std;

class Trajectory {
public:
    Trajectory(); //overloaded const
    Trajectory( const Input &myInput, Direction direction); //overloaded constructor (makes first traj)
	Trajectory( const Input &myInput, const Config &myConfig, Direction direction, int m_n_slices);
	
	
	//makes trajectory snippets.
	void MergeTrajectories(const Trajectory &snippet, int firstSliceToErase, int lastSliceToErase, Side currSide, Direction currDir);
	int getLengthOfTraj() const;
	const Slice& GetSlice(int indicator) const;
	int GetOrderParameter(int firstSlice, int lastSlice) const;
	void printTrajectory(int indicator) const;
    virtual ~Trajectory(); //destructor
	//some getters and setters
    //void setInfo(int _old, int _new,long currStep);

	//public variables
	//long int idum=-1; 
	
private:
	//functions
	//float ran2;
	//member variables
	//slice m_trajectory[NSLICESMAX];
	deque<Slice> m_traj;
	double m_density;
	int m_length;
	double m_n_slices;
	double m_n_slices_full;
	double m_tObs;
	int m_sizeOfSystem;
	
	//double m_J;
	//double m_temp;
	//config array, starts and 0 and goes to length^2
	
	friend class Slice; 
};

#endif /*_TRAJECTORY_H*/
