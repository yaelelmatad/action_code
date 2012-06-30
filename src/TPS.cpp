/*
 *  TPS.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 06/2012
 *  Copyright 2012. All rights reserved.
 *
 */

#include "TPS.h"

TPS::TPS( const Input &myInput, double s)
{
	m_s=s;
	m_input = myInput;
	m_n_slices_shift = myInput.GetIntInput(N_SLICES_SHIFT);
	m_n_slices = myInput.GetIntInput(N_SLICES);
	m_shoot_frac = myInput.GetDoubleInput(D_SHOOT_FRACTION);
		
}

void TPS::SetS(double tempS)
{
	m_s = tempS;
}

void TPS::TPS_move( const Trajectory &myTraj)
{
	int shootOrShift = ShootOrShift();
	int direction = ForwardsOrBackwards();
	int slicesToRegen = SlicesToRegenerate();
	shootOrShift = SHOOT;
	direction = FORW;
	
	if (shootOrShift == SHOOT && direction == FORW)
		ShootForward(myTraj, slicesToRegen);
	else if (shootOrShift == SHOOT && direction == BACK)
		ShootBackward(myTraj, slicesToRegen);
	else if (shootOrShift == SHIFT && direction == FORW)
		ShiftForward(myTraj, slicesToRegen);
	else 
		ShiftBackward(myTraj, slicesToRegen);
	
}

void TPS::ShootForward(const Trajectory &myTraj, int regenSlices) const
{
	int firstKept = 0;
	cout << "firstKept " << firstKept<< endl;

	int lastKept = m_n_slices - 1 - regenSlices;
	cout << "lastKept " << lastKept<< endl;
	//last slice is m_n_slices -1.  

	//slices from first and last trajectory to "keep"
	const Slice lastKeptSlice = myTraj.GetSlice(lastKept+1);
	const Config lastConfig = lastKeptSlice.GetLastConfig();
	
	Trajectory snippet(m_input, lastConfig, EDirection_FORWARD, regenSlices);
	
	double oldOrderParameter = (double)(myTraj.GetOrderParameter(lastKept+1,m_n_slices-1));
	double newOrderParameter = (double)(snippet.GetOrderParameter(0,regenSlices-1));
	cout << oldOrderParameter << " " << newOrderParameter << endl;
	
	bool acceptance = AcceptOrReject(newOrderParameter, oldOrderParameter);
	if (acceptance)
		cout << "Trajectory Accepted! \n";
	else {
		cout << "Trajectory Rejected!" << endl;
	}

	
}

bool TPS::AcceptOrReject(double newOP, double oldOP) const
{
	double boltz = exp(-(newOP-oldOP)*m_s);
	cout << "boltz = " << boltz << endl;
	double randNum = ((double)rand()/(double)RAND_MAX);
	cout << randNum << endl;
	if (randNum <= boltz)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void TPS::ShootBackward(const Trajectory &myTraj, int nslices) const
{
	
}

void TPS::ShiftBackward(const Trajectory &myTraj, int nslices) const
{

}

void TPS::ShiftForward(const Trajectory &myTraj, int nslices) const
{

}





int TPS::SlicesToRegenerate() const
{
	double rand1 =((double)rand()/((double)RAND_MAX+1));
	double randNum =rand1*m_n_slices_shift;
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