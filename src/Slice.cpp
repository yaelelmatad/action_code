/*
 *  Slice.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 6/12.
 *  Copyright 2012. All rights reserved.
 *
 */

#include "Slice.h"

Slice::Slice(){
}

//make a class called config, config should know it's size TODO, configs should have the list.

Slice::Slice( const Input& myInput, const Config &currentConfig, bool first)
{
	//if first = true then we are going "forward" otherwise going backwards. 
	
	Dynamics currentDynamics(myInput);
	double slicesDouble = static_cast<double>( myInput.GetIntInput(N_SLICES) );
	double tOBS = myInput.GetDoubleInput(D_TOBS);
	m_timeInterval = tOBS/slicesDouble;
	
	if (first)
	{
		m_firstConfig = currentConfig;
		m_lastConfig = currentConfig;
		currentDynamics.UpdateConfig(&m_lastConfig, m_timeInterval );
		//LIST STUFF GOES HERE
	}
	else 
	{
		m_lastConfig = currentConfig;
		m_firstConfig = currentConfig;
		currentDynamics.UpdateConfig(&m_firstConfig, m_timeInterval );
		//LIST STUFF GOES HERE
	}
	/*
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
	 */
	
}

void Slice::printFirstConfig(ofstream &outputFile, double time) const
{
	m_firstConfig.printConfig(outputFile, time);
}

void Slice::printLastConfig(ofstream &outputFile, double time) const
{
	m_lastConfig.printConfig(outputFile, time);
}

const Config& Slice::GetFirstConfig() const
{
	return m_firstConfig;
}

const Config& Slice::GetLastConfig() const
{
	return m_lastConfig;
}

Slice::~Slice(){
}

