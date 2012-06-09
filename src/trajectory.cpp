/*
 *  trajectory.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 8/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "trajectory.h"

trajectory::trajectory(){
}

trajectory::trajectory(double temp, double density, int length, double J)
{
	m_temp = temp;
	m_density = density;
	m_length = length;
	m_J = J;
}


trajectory::~trajectory(){
}

