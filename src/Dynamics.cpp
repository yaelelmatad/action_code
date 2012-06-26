/*
 *  dynamics.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 06/12
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Dynamics.h"

//dynamics::dynamics(){
//}


Dynamics::Dynamics( const Input &myInput)
{	
	m_temp = myInput.GetDoubleInput(D_TEMP);

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
	/*
	cout << m_epsilon << endl;
	cout << m_leftRate << endl;
	cout << m_rightRate << endl;
	cout << m_cprob << endl;
	*/
	
}

void Dynamics::UpdateConfig( Config* pConfig, double interval ) const
{
	Config& toUpdate = *pConfig;
	
	double time = 0;
	
	double totalRate = GetTotalRate( toUpdate );
	
	/*
	for (int i = 0; i< toUpdate.m_length; i++)
	{
		cout << toUpdate.m_cell[i] << " ";
	}
	*/
	
	while (time < interval)
	{
		//cout << " Current Time = " << time << endl;
		//cout << " Current m_config().m_cell[] Array Is: ";
		//cout << endl;
		time += m_pickATime( totalRate );
		PickAndFlipSpin( toUpdate, totalRate );
		toUpdate.CheckListIntegrity();
		totalRate = GetTotalRate( toUpdate );
		
		/*
		for (int i = 0; i< toUpdate.m_length; i++)
		{
			cout << toUpdate.m_cell[i] << " ";
		}
		*/
	}
	
	//cout << endl;
	
}

void Dynamics::InitializeRates()
{
	//MODEL DEPENDANT!  
	//initializes the total rate of hte system. //in the future only need to do "local" changes.
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
	double result = 0.0;
	
	for (int i = 0; i < NUM_LISTS; i++)
	{
		result += m_rates[i]*((double)localConfig.m_lists[i][0]);
	}
	
	return result;
}

void Dynamics::PickAndFlipSpin( Config& toUpdate, double totalRate ) const
{
	//based on rate lists pick a spin to flip from the lists.  doesn't flip the spin!
	
	double random = ((double)rand()/(double)RAND_MAX)* totalRate; //picks a random number from 0->m_totalRate
	int i = -1;
	bool notYetFoundList = true;
	double nextRateCeiling = 0;
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
	
	//cout << "picked a list random number was " << random << " picked list " << i << endl;
	
	//now pick a random spin on that list
	int random_int = rand()%(toUpdate.m_lists[i][0])+1; //first pick rand num from 0->(num on list -1) then add 1 to go from 1->num on list
	
	//cout << "picked a spin random number " << m_config().m_lists[i][random_int] << endl;
	
	int spinToFlip = toUpdate.m_lists[i][random_int];
	
	toUpdate.m_flipSpin(spinToFlip);
}

double Dynamics::m_pickATime( double totalRate ) const
{
	
	double random = ((double)rand()/(double)RAND_MAX); //random number 0->1
	double deltaTime = (-log(random)/totalRate);
	return deltaTime;
}
