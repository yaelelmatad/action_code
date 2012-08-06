/*
 *  trajectory.h
 *  
 *
 *  Created by Yael Elmatad on 6/12
 *  Copyright 2012. All rights reserved.
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
	//takes the "snippet" and merges itno "this" trajectory.  erases from firstSlicetoErase to lastSlicetoErase inclusive.
	//currSide means whether ot add to beginning or end.
	//currDir is which way the snippet trajectory was run, but I believe only fwd is actually implemented.
	
	int GetLengthOfTraj() const;
	//gets the number of slices in the traj.
	
	const Slice& GetSlice(int indicator) const;
	//gets the slice at position "indicator"
	
	int GetOrderParameter(int firstSlice, int lastSlice) const;
	//gets the trajectory order parameter (for KCMs = K = number of events)
	
	void PrintTrajectory(int rank, int indicator, double S) const;
	//prints trajectory (and makes the name of the file for it to be printed.  takes the process rank (ie which processor), indicator (ie the traj #) and the current value of S
	//where S is some distinguishing parameter between the ranks (like Temp or the S from the s-ensemble).  
	
    void PrintRestartTraj(FILE* outputFile) const;
	//prints the current instance for the restart trajectory (calls the printslice/print config routines)
	
	void LoadRestartTraj(FILE* inputFile); 
	//loads a restarted trajectory into the current instance.
	
	void EraseOrderParameterFile(double param) const;
	//clears out the order parameter
	
	void PrintOrderParameter(double param) const;
	//prints the order parameter to the order parameter file (determines the file name from the param.  for KCMs param = s, but could be temp)
	
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
	//the container for the slices, deque = double ended queue

	double m_n_slices;
	//number of slices in this instance of traj (from input for full and from constructor for snippet)
	
	double m_n_slices_full;
	//m_n_slices_full from input, only used in print routine to determine the time interval for printing.
	
	double m_tObs;
	//time length of traj, only used in print routine to determine the time interval for printing
		
	void EraseFile(char* fle) const;
	//erases the file, used for the print routines
	
	//double m_J;
	//double m_temp;
	//config array, starts and 0 and goes to length^2
	
	friend class Slice; 
};

#endif /*_TRAJECTORY_H*/
