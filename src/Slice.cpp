/*
 *  slice.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 8/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Slice.h"

Slice::Slice(){
}

//make a class called config, config should know it's size TODO, configs should have the list.

Slice::Slice(Input& myInput, Config &currentConfig, bool first)
{
	//if first = true then we are going "forward" otherwise going backwards. 
	
	Dynamics currentDynamics(myInput);
	double slicesDouble = (double)myInput.getIntInput(N_SLICES);
	double tOBS = myInput.getDoubleInput(D_TOBS);
	m_timeInterval = tOBS/slicesDouble;
	
	
	if (first)
	{
		m_firstConfig = currentConfig;
		currentDynamics.UpdateConfig(&currentConfig, m_timeInterval );
		//LIST STUFF GOES HERE
		m_lastConfig = currentConfig;
	}
	else 
	{
		m_lastConfig = currentConfig;
		currentDynamics.UpdateConfig(&currentConfig, m_timeInterval );
		//LIST STUFF GOES HERE
		m_firstConfig = currentConfig;
	}
	
	cout << "firstConfig \n";
	for (int i = 0; i < myInput.getIntInput(N_SITES_FULL); i++)
	{
		cout << m_firstConfig.getConfig(i) << " ";
	}
	cout << endl;
	cout << endl;
	cout << "lastConfig \n";
	for (int i = 0; i < myInput.getIntInput(N_SITES_FULL); i++)
	{
		cout << m_lastConfig.getConfig(i) << " ";
	}
	cout << endl;
	cout << endl;
	
}

Slice::~Slice(){
}

