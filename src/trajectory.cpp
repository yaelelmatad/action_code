/*
 *  trajectory.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 8/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Trajectory.h"

Trajectory::Trajectory(){
}

Trajectory::Trajectory(Input &myInput)
{
	m_n_slices = myInput.getIntInput(N_SLICES);
	//cout << m_n_slices << endl;
	//Slice testSlice(test2, true, 10);
	m_traj.resize(m_n_slices+1);
	//m_traj[0]=testSlice;
	//cout << m_traj.size() << endl;
	m_traj.clear();
	m_length = myInput.getDoubleInput(D_TOBS);
	//m_J = J;
}


Trajectory::~Trajectory(){
}

