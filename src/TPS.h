/*
 *  TPS.h
 *  
 *
 *  Created by Yael Elmatad on 6/2012
 *  Copyright 2012. All rights reserved.
 *
 */


#ifndef _TPS_H
#define	_TPS_H
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

#define MAXSIZE 10000

//#include "Slice.h"
#include "Trajectory.h"
#include "Input.h"


enum ShootOrShift{
	SHOOT,
	SHIFT
};

enum Dir{
	FORW,
	BACK
};

/*enum OccState
 {
 OCCUPIED,
 UNOCCUPIED,
 };*/

using namespace std;

class TPS {
public:
    TPS(const Input &); //overloaded const
	void TPS_move(const Trajectory &);
	//makes trajectory snippets.
//	void printTrajectory(int indicator) const;
	//some getters and setters
    //void setInfo(int _old, int _new,long currStep);
	
	//public variables
	//long int idum=-1; 
	
private:
	int m_n_slices;
	int m_n_slices_shift;
	double m_shoot_frac;
	int SlicesToRegenerate() const;	
	int ShootOrShift() const;
	int ForwardsOrBackwards() const;
	
	void ShootBackward(const Trajectory &myTraj, int nSlices);
	void ShootForward(const Trajectory &myTraj, int nslices);
	void ShiftBackward(const Trajectory &myTraj, int nslices);
	void ShiftForward(const Trajectory &myTraj, int nslices);

	//friend class Trajectory; 
};

#endif /*_TPS_H*/