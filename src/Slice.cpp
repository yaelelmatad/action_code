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
	return (double)m_K;
}

int Slice::GetOrderParam() const
{
	return m_K;
}


void Slice::PrintRestartSlice(FILE* outputFile, int index) const
{
	m_firstConfig.PrintRestartConfig(outputFile, index);
	m_lastConfig.PrintRestartConfig(outputFile, index);

	//print K
	fprintf(outputFile, "%i %i \n", index, m_K);

	
	
}

void Slice::LoadRestartSlice(FILE* inputFile, int index)
{
	m_firstConfig.LoadRestartConfig(inputFile, index);
	m_lastConfig.LoadRestartConfig(inputFile, index);
	
	//print K
	fscanf(inputFile, "%i %i \n", &index, &m_K);
	//cout << "m_K " << m_K << endl;
	
	
	
}



void Slice::printFirstConfig(ofstream &outputFile, double time) const
{
	m_firstConfig.printConfig(outputFile, time);
}

void Slice::printLastConfig(ofstream &outputFile, double time) const
{
	m_lastConfig.printConfig(outputFile, time);
}

const Config& Slice::GetSeedConfig(Direction direction) const
{
	return ( direction == EDirection_BACKWARD ) ? GetFirstConfig() : GetLastConfig();
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

