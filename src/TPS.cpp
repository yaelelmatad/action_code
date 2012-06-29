/*
 *  TPS.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 06/2012
 *  Copyright 2012. All rights reserved.
 *
 */

#include "TPS.h"

TPS::TPS( const Input &myInput)
{
	m_n_slices_shift = myInput.GetIntInput(N_SLICES_SHIFT);
	m_n_slices = myInput.GetIntInput(N_SLICES);
	m_shoot_frac = myInput.GetDoubleInput(D_SHOOT_FRACTION);
		
}

void TPS::TPS_move( const Trajectory &myTraj)
{
	int shootOrShift = ShootOrShift();
	int direction = ForwardsOrBackwards();
	int slicesToRegen = SlicesToRegenerate();
	
	if (shootOrShift == SHOOT && direction == FORW)
		ShootForward(myTraj, slicesToRegen);
	else if (shootOrShift == SHOOT && direction == BACK)
		ShootBackward(myTraj, slicesToRegen);
	else if (shootOrShift == SHIFT && direction == FORW)
		ShiftForward(myTraj, slicesToRegen);
	else 
		ShiftBackward(myTraj, slicesToRegen);
	
}

void TPS::ShootBackward(const Trajectory &myTraj, int nSlices)
{
	int lastOldSlice = m_n_slices - 1 - nSlices;
	//last slice is m_n_slices -1.  
	
	
}

void TPS::ShootForward(const Trajectory &myTraj, int nslices)
{
	
}

void TPS::ShiftBackward(const Trajectory &myTraj, int nslices)
{

}

void TPS::ShiftForward(const Trajectory &myTraj, int nslices)
{

}





int TPS::SlicesToRegenerate() const
{
	double randNum = ((double)rand()/((double)RAND_MAX+1))*m_shoot_frac+1;
	//doing this +1 thing ensures that the rand part returns a number between [0,N_SLICES_SHIFT)
	//thus adding one can and making an int would give the range [1,N_SLICES_SHIFT];
	return ((int)randNum);
	
}


int TPS::ShootOrShift() const
{
	
	double randNum = ((double)rand()/(double)RAND_MAX);
	if (randNum < D_SHOOT_FRACTION)
	{
		return SHOOT;
	}
	else 
	{
		return SHIFT;
	}
	
}

int TPS::ForwardsOrBackwards() const
{
	double randNum = ((double)rand()/(double)RAND_MAX);
	if (randNum < 0.5)
	{
		return FORW;
	}
	else 
	{
		return BACK;
	}

	
}