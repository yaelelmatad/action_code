/*
 *  dynamics.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 8/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "dynamics.h"

//dynamics::dynamics(){
//}


dynamics::dynamics( config &currentConfig, double temp, double u, bool hard, double rate_left, double rate_right)
:	p_curr_config( &currentConfig )
{
	m_temp = temp;
	if (hard)
	{
		m_epsilon = 0;
	}
	else 
	{
		m_epsilon = exp(-u/temp);
	}
	m_leftRate = rate_left;
	m_rightRate = rate_right;
	m_cprob = (exp(-1.0/m_temp));
	m_setTotalRate();
	
	
}

config& dynamics::m_getCurrConfig()
{
	return m_config();
}

void dynamics::m_advanceDynamics(double interval)
{
	double time = 0;
	
	while (time < interval)
	{
		//cout << " Current Time = " << time << endl;
		//cout << " Current m_config().m_config[] Array Is: ";
		
		for (int i = 0; i<m_config().m_length; i++)
			cout << m_config().m_config[i] << " ";
		
		cout << endl;
		time += m_pickATime();
		m_pickAndFlipSpin();
		m_config().m_checkListIntegrity();
		m_updateTransRate();
	}
	
	return;
}

void dynamics::m_setTotalRate()
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

	m_totalRate = 0;
	for (int i = 0; i < NUM_LISTS; i++)
	{
		m_totalRate += m_rates[i]*((double)m_config().m_lists[i][0]);;
	}
	
	
	/*
	m_totalRate = m_cprob*m_epsilon*((double)m_config().m_lists[NOTFACDOWN][0]);
	m_totalRate += m_epsilon*((double)m_config().m_lists[NOTFACUP][0]);
	m_totalRate += m_cprob*(m_leftRate+ m_epsilon)*((double)m_config().m_lists[FACLEFTDOWN][0]);
	m_totalRate += (m_leftRate+ m_epsilon)*((double)m_config().m_lists[FACLEFTUP][0]);
	m_totalRate += m_cprob*(m_rightRate+ m_epsilon)*((double)m_config().m_lists[FACRIGHTDOWN][0]);
	m_totalRate += (m_rightRate+ m_epsilon)*((double)m_config().m_lists[FACRIGHTUP][0]);	
	m_totalRate += m_cprob*(m_rightRate + m_leftRate + m_epsilon)*((double)m_config().m_lists[FACBOTHDOWN][0]);
	m_totalRate += (m_rightRate + m_leftRate + m_epsilon)*((double)m_config().m_lists[FACBOTHUP][0]);
	*/
}


void dynamics::m_pickAndFlipSpin()
{
	//based on rate lists pick a spin to flip from the lists.  doesn't flip the spin!
	
	double random = ((double)rand()/(double)RAND_MAX)*m_totalRate; //picks a random number from 0->m_totalRate
	int i = -1;
	bool notYetFoundList = true;
	double nextRateCeiling = 0;
	while(notYetFoundList && i < NUM_LISTS)
	{
		i++;
		nextRateCeiling += m_rates[i]*((double)m_config().m_lists[i][0]);
		if (random < nextRateCeiling)
		{
			notYetFoundList = false;
		}

	}
	
	if (notYetFoundList)
		cout << "Warning: m_pickASpin ended without picking a spin\n";
	
	//cout << "picked a list random number was " << random << " picked list " << i << endl;
	
	//now pick a random spin on that list
	int random_int = rand()%(m_config().m_lists[i][0])+1; //first pick rand num from 0->(num on list -1) then add 1 to go from 1->num on list
	
	//cout << "picked a spin random number " << m_config().m_lists[i][random_int] << endl;

	int spinToFlip = m_config().m_lists[i][random_int];

	m_config().m_flipSpin(spinToFlip);

	return;
	

	
}

double dynamics::m_updateTransRate()
{
	m_setTotalRate(); //for now, later can make more efficient.
	//not yet finished, updates the transition rates locally given a 
	return 1.0;
	
}

double dynamics::m_pickATime()
{
	
	double random = ((double)rand()/(double)RAND_MAX); //random number 0->1
	double deltaTime = (-log(random)/m_totalRate);
	return deltaTime;
}

dynamics::~dynamics(){
}

