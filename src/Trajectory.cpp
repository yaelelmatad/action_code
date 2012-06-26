/*
 *  Trajectory.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 06/2012
 *  Copyright 2012. All rights reserved.
 *
 */

#include "Trajectory.h"

Trajectory::Trajectory(){
}

Trajectory::Trajectory( const Input &myInput, Direction direction)
{
	//constructor that makes a FULL trajectory
	//must be submitted via input!
	m_n_slices = myInput.GetIntInput(N_SLICES);
	m_n_slices_full = m_n_slices;
	m_tObs = myInput.GetDoubleInput(D_TOBS);
	m_traj.resize(m_n_slices+1);
	m_traj.clear();
	Config myConfig(myInput);
	int i;
	
	//Direction direction = EDirection_BACKWARD;
	if (direction == EDirection_FORWARD)
		i = 0;
	
	if (direction == EDirection_BACKWARD)
		i=m_n_slices-1;
	
	m_traj[i] = Slice(myInput, myConfig, direction );
	for (i+=direction; i < m_n_slices && i >= 0; i+=direction)
	{
		m_traj[i] = Slice(myInput, m_traj[i-direction].GetSeedConfig( direction ), direction );
	}
	
}

Trajectory::Trajectory( const Input &myInput, const Config &myConfig, Direction direction, int n_slicesSnip)
{
	//constructor capable of making a snippet from a seed config.
	m_n_slices = n_slicesSnip;
	m_n_slices_full = myInput.GetIntInput(N_SLICES);
	m_tObs = myInput.GetDoubleInput(D_TOBS);
	m_traj.resize(m_n_slices+1);
	m_traj.clear();
	//Config myConfig(myInput);
	int i;
	
	//Direction direction = EDirection_BACKWARD;
	if (direction == EDirection_FORWARD)
		i = 0;
	
	if (direction == EDirection_BACKWARD)
		i=m_n_slices-1;
	
	m_traj[i] = Slice(myInput, myConfig, direction );
	for (i+=direction; i < m_n_slices && i >= 0; i+=direction)
	{
		m_traj[i] = Slice(myInput, m_traj[i-direction].GetSeedConfig( direction ), direction );
	}
	
}


void Trajectory::printTrajectory(int indicator) const
{
	double interval = m_tObs/m_n_slices_full;
	double time = 0;
	//Config currConfig;
	string filename ("traj");
	std::ostringstream oss;
	oss << indicator;
	filename += oss.str();
	filename += ".dat";
	
	cout << "m_n_slices = " << m_n_slices << endl;

	cout << filename << endl;
	
	ofstream outputFile;
	outputFile.open(filename.c_str());
	
	//pass to slice which passes to config (slice and traj therefore don't need to know how a config "looks", just pass the time along
	for (int i = 0; i < m_n_slices; i++)
	{
		m_traj[i].printFirstConfig(outputFile, time);				
		time += interval;
	}

	m_traj[m_n_slices-1].printLastConfig(outputFile, time);				
}



Trajectory::~Trajectory(){	
}

