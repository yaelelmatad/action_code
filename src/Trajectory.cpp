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

Trajectory::Trajectory( const Input &myInput, const Config &myConfig)
{
	m_n_slices = myInput.GetIntInput(N_SLICES);
	m_tObs = myInput.GetDoubleInput(D_TOBS);
	m_sizeOfSystem = myInput.GetIntInput(N_SITES_FULL);
	m_traj.resize(m_n_slices+1);
	m_traj.clear();
	
	for (int i = 0; i < m_n_slices; i++)
	{
		m_traj[i] = Slice(myInput, myConfig, true);
	
	}
	
}

void Trajectory::printTrajectory(int indicator) const
{
	double interval = m_tObs/(double)m_n_slices;
	double time = 0;
	//Config currConfig;
	string filename ("traj");
	std::ostringstream oss;
	oss << indicator;
	filename += oss.str();
	filename += ".dat";
	

	cout << filename << endl;
	
	ofstream outputFile;
	outputFile.open(filename.c_str());
	
	//pass to slice which passes to config (slice and traj therefore don't need to know how a config "looks", just pass the time along
	for (int i = 0; i < m_n_slices; i++)
	{
		for (int j = 0; j< m_sizeOfSystem; j++)
			{
				m_traj[i].printFirstConfig(outputFile, time);				
			}
		time += interval;

	}

	for (int j = 0; j< m_sizeOfSystem; j++)
	{
		m_traj[m_n_slices-1].printLastConfig(outputFile, time);				
	}
	
	
}



Trajectory::~Trajectory(){	
}

