/*
 *  Slice.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 6/12.
 *  Copyright 2012. All rights reserved.
 *
 */

#include "Slice.h"

#include "Dynamics.h"
#include "Input.h"

#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

Slice::Slice(){
}

//make a class called config, config should know it's size TODO, configs should have the list.

Slice::Slice( const Input& myInput, const Config &currentConfig, Direction direction )
{
	//if first = true then we are going "forward" otherwise going backwards. 
	
	Dynamics currentDynamics(myInput);
	double slicesDouble = static_cast<double>( myInput.GetIntInput(N_SLICES) );
	double tOBS = myInput.GetDoubleInput(D_TOBS);
	m_timeInterval = tOBS/slicesDouble;
	m_K = 0;
	
	if ( direction == EDirection_FORWARD )
	{
		m_firstConfig = currentConfig;
		m_lastConfig = currentConfig;
		UpdateConfig(currentDynamics, m_lastConfig, m_timeInterval);
		//currentDynamics.UpdateConfig(&m_lastConfig, m_timeInterval );
		//LIST STUFF GOES HERE
	}
	else 
	{
		// std::assert( direction == EDirection_BACKWARD );
		
		m_lastConfig = currentConfig;
		m_firstConfig = currentConfig;
		UpdateConfig(currentDynamics, m_firstConfig, m_timeInterval);
		//currentDynamics.UpdateConfig(&m_firstConfig, m_timeInterval );
		//LIST STUFF GOES HERE
	}
	/*
	cout << "firstConfig \n";
	for (int i = 0; i < myInput.GetIntInput(N_SITES_FULL); i++)
	{
		cout << m_firstConfig.getConfig(i) << " ";
	}
	cout << endl;
	cout << endl;
	cout << "lastConfig \n";
	for (int i = 0; i < myInput.GetIntInput(N_SITES_FULL); i++)
	{
		cout << m_lastConfig.getConfig(i) << " ";
	}
	cout << endl;
	cout << endl;
	 */
	
}

void Slice::UpdateConfig(const Dynamics& currDynamics, Config& confToUpdate, double interval)
{
	//updates the config for a time interval.  
	//calls the dynamics update ConfigOneStep routine (which does just ONE move at a time here
	//could be any kind of move though, including a constant time interval move
	//updateActionParam
	//also updates action param (which are stored in the slice)
	double time = 0; 
	
	while (time < interval)
	{
		time += currDynamics.UpdateConfigOneStep(&confToUpdate);
		UpdateActionParameters();
	}
		
}

void Slice::UpdateActionParameters()
{
	//DEPENDS ON WHAT YOU WANT TO STORE.  CURRENTLY JUST STORING K
	
	m_K++;
	
		
}

double Slice::GetOrderParamDouble() const
{
	//in case you need a double version of the param
	return (double)m_K;
}

int Slice::GetOrderParam() const
{
	//returns the int value if needed
	return m_K;
}


void Slice::PrintRestartSlice(FILE* outputFile, int index) const
{
	//prints the slice (first and last config) to an formatted outputFile for restarting
	m_firstConfig.PrintRestartConfig(outputFile, index);
	m_lastConfig.PrintRestartConfig(outputFile, index);

	//print K
	fprintf(outputFile, "%i %i \n", index, m_K);

	
	
}

void Slice::LoadRestartSlice(FILE* inputFile, int index)
{
	//loads the first and last config from a formmated restart file
	m_firstConfig.LoadRestartConfig(inputFile);
	m_lastConfig.LoadRestartConfig(inputFile);
	
	//load K
	fscanf(inputFile, "%i %i \n", &index, &m_K);
	
	
	
}

void Slice::printFirstConfig(ofstream &outputFile, double time) const
{
	//prints the first config (for gnuplot plotting)
	m_firstConfig.PrintConfig(outputFile, time);
}

void Slice::printLastConfig(ofstream &outputFile, double time) const
{
	//prints the last config (for gnuplot plotting)
	m_lastConfig.PrintConfig(outputFile, time);
}

const Config& Slice::GetSeedConfig(Direction direction) const
{
	//depending on directon of dynamics returns either the first or last config (for the next slice)
	return ( direction == EDirection_BACKWARD ) ? GetFirstConfig() : GetLastConfig();
}

const Config& Slice::GetFirstConfig() const
{
	//returns the first config
	return m_firstConfig;
}

const Config& Slice::GetLastConfig() const
{
	//returns the last config
	return m_lastConfig;
}

Slice::~Slice(){
}

