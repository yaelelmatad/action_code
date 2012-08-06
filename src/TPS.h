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
#include <deque>
#include <string>
#include <sstream>

#define MAXSIZE 10000

#include "Slice.h"
#include "Trajectory.h"
#include "Input.h"


enum ShootOrShift{
	SHOOT,
	SHIFT
};

enum Dir{
	FORW = 1,
	BACK = -1
};


/*enum OccState
 {
 OCCUPIED,
 UNOCCUPIED,
 };*/

using namespace std;

class TPS {
public:
	TPS();
	//default constructor, does nothing
    
	TPS(const Input &, int my_rank, int comm_sz);
	//constructor which takes the input as well as the rank of the processor and the number of total processors 
	
	void TPS_move( Trajectory &);
	//one TPS move (shoot/shift,etc...)
	
	void SetS(double S);
	//sets current value of S
	
	void SetFirstS(double start_s, double end_s, int my_rank, int comm_sz);
	//initalizes the S values to go from start -> end in even spacing across comm_sz.  later on shoudl be set directly when swapping for parallel tempering
	
	double GetCurrS() const;
	//gets the current value of S for this rank
	
private:
	int m_n_slices;
	//number of slices (total)
	
	int m_n_slices_shift;
	//max TPS move size
	
	double m_s;
	//current value of S
	
	double m_shoot_frac;
	//percent of shoots vs shift to do (0.5 is even, 1 is all shoots, 0 is all shifts)
	
	Input m_input;
	//current isntance of the input class
	
	//Slice tempSlice;
	//garbage?
	
	
	int SlicesToRegenerate() const;	
	//number of slices to regenerate
	
	int ShootOrShift() const;
	//returns shoot or shift;
	
	int ForwardsOrBackwards() const;
	//returns directionality (50:50)
	
	bool AcceptOrReject(double newOP, double oldOP) const;
	//determines if move should be accepted or rejected.  based on OP difference (for s-ensemble TPS)
	
	void ShootBackward( Trajectory &myTraj, int regenSlices) const;
	//takes the traj myTraj and does a TPS move on it (backwards shooting).  Regenerates regenSlices and then checks for acceptances  If accepted it calls the merge traj routine
	
	void ShootForward( Trajectory &myTraj, int regenSlices) const;
	//takes the traj myTraj and does a TPS move on it (forward shooting).  Regenerates regenSlices and then checks for acceptances  If accepted it calls the merge traj routine

	void ShiftBackward( Trajectory &myTraj, int regenSlices) const;
	//takes the traj myTraj and does a TPS move on it (backwards shifting).  Regenerates regenSlices and then checks for acceptances  If accepted it calls the merge traj routine

	void ShiftForward( Trajectory &myTraj, int regenSlices) const;
	//takes the traj myTraj and does a TPS move on it (forward shifting).  Regenerates regenSlices and then checks for acceptances  If accepted it calls the merge traj routine

};

#endif /*_TPS_H*/