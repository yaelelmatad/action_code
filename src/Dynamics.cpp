/*
 *  dynamics.cpp
 *  Action
 *
 *	current implement dynamics = continous time monte carlo
 *
 *  Created by Yael Elmatad on 06/12
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

// Class header
#include "Dynamics.h"

// Other includes
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <float.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "Config.h"
#include "Input.h"

//dynamics::dynamics(){
//}



Dynamics::Dynamics( const Input &myInput)
{	
	//gets relevent input paramters from input file
	m_temp = myInput.GetDoubleInput(D_TEMP);

	//if the system is hard needs to be set automatically. (because D_U cannot be infinite)
	if (myInput.GetIntInput(N_HARD)==0)
	{
		m_epsilon = 0;
	}
	else 
	{
		m_epsilon = exp(-myInput.GetDoubleInput(D_U)/m_temp);
	}
	m_leftRate = myInput.GetDoubleInput(D_RATE_LEFT);
	m_rightRate = myInput.GetDoubleInput(D_RATE_RIGHT);
	m_cprob = (exp(-1.0/m_temp));
	
	InitializeRates();
}


double Dynamics::UpdateConfigOneStep( Config* pConfig ) const
{
	//does one config move, returns the time to do that one step
	Config& toUpdate = *pConfig;
	
	double time ;
	
	double totalRate = GetTotalRate( toUpdate );


	time = PickATime( totalRate );
	PickAndFlipSpin( toUpdate, totalRate );
	//A small check, use if necessary
	//toUpdate.CheckListIntegrity();
	
	return time;
		
}

// #define PRINT_DYNAMICS_OUTPUT

void Dynamics::UpdateConfigBlock( Config* pConfig, double interval ) const
{
	Config& toUpdate = *pConfig;
	
	double time = 0;
	
	double totalRate = GetTotalRate( toUpdate );
	
#ifdef PRINT_DYNAMICS_OUTPUT
	toUpdate.PrintDynamicsCells();
#endif
	
	while (time < interval)
	{
#ifdef PRINT_DYNAMICS_OUTPUT
		cout << " Current Time = " << time << endl;
		cout << " Current m_config().m_cell[] Array Is: ";
		cout << endl;
#endif


	while (time < interval)
	{
		time += PickATime( totalRate );
		PickAndFlipSpin( toUpdate, totalRate );
		totalRate = GetTotalRate( toUpdate );
		
#ifdef PRINT_DYNAMICS_OUTPUT
		toUpdate.PrintDynamicsCells();
#endif
	}
	
#ifdef PRINT_DYNAMICS_OUTPUT
	cout << endl;
#endif
		//a small check, use if necessary
		//toUpdate.CheckListIntegrity();
	}
}

void Dynamics::InitializeRates()
{
	//MODEL DEPENDANT!  
	//initializes the "base" rate of each type of move. 
	m_rates[NOTFACDOWN] = m_cprob*m_epsilon;
	m_rates[NOTFACUP] = m_epsilon;
	m_rates[FACLEFTDOWN] = m_cprob*(m_leftRate+ m_epsilon);
	m_rates[FACLEFTUP]=(m_leftRate+ m_epsilon);
	m_rates[FACRIGHTDOWN]=m_cprob*(m_rightRate+ m_epsilon);
	m_rates[FACRIGHTUP]=(m_rightRate+ m_epsilon);	
	m_rates[FACBOTHDOWN]=m_cprob*(m_rightRate + m_leftRate + m_epsilon);
	m_rates[FACBOTHUP]=(m_rightRate + m_leftRate + m_epsilon);
}


double Dynamics::GetTotalRate( const Config& localConfig ) const
{
	//mutliplying base rates by number of things in that list gives the total rate (used for updating the time). returns this rate.
	double result = 0.0;
	
	for (int i = 0; i < NUM_LISTS; i++)
	{
		result += m_rates[i]*(static_cast<double>(localConfig.m_lists[i][0]));
	}
	return result;
}

void Dynamics::PickAndFlipSpin( Config& toUpdate, double totalRate ) const
{
	//based on rate lists pick a spin to flip from the lists.  doesn't flip the spin!
	
	double random = ((double)rand()/(double)RAND_MAX)* totalRate; //picks a random number from 0->m_totalRate
	//since we increment i right away start it out at -1
	int i = -1;
	bool notYetFoundList = true;
	double nextRateCeiling = 0;
	//if the number is between the previous "rateCeiling" and the following one due to the next added list, pick a spin from the next added list
	while(notYetFoundList && i < NUM_LISTS)
	{
		i++;
		nextRateCeiling += m_rates[i]*((double)toUpdate.m_lists[i][0]);
		if (random < nextRateCeiling)
		{
			notYetFoundList = false;
		}		
	}
	
	if (notYetFoundList)
		cout << "Warning: m_pickASpin ended without picking a spin\n";
	
	//now pick a random number from 1 to number of spins on that list on that list
	int random_int = rand()%(toUpdate.m_lists[i][0])+1; //first pick rand num from 0->(num on list -1) then add 1 to go from 1->num on list
	
	//find that spin
	int spinToFlip = toUpdate.m_lists[i][random_int];
	
	//flip it
	toUpdate.FlipSpin(spinToFlip);
}

double Dynamics::PickATime( double totalRate ) const
{
	//picks an update time (time interval) based on the lists 
	double random = ((double)rand()/(double)RAND_MAX); //random number 0->1
	double deltaTime = (-log(random)/totalRate);
	return deltaTime;
}

