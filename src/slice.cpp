/*
 *  slice.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 8/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "slice.h"

slice::slice(){
}

/*
slice::slice( const config& xRef )
:	m_firstConfig( xRef )
{
	
}
 */

//make a class called config, config should know it's size TODO, configs should have the list.

slice::slice(input& myInput, dynamics &currentDynamics, bool first)
:	p_curr_dynamics( &currentDynamics )
{
	//if first = true then we are going "forward" otherwise going backwards. 
//	m_temp = temp;
	double slicesDouble = (double)myInput.getIntInput(N_SLICES);
	double tOBS = myInput.getDoubleInput(D_TOBS);
	m_timeInterval = tOBS/slicesDouble;
//	m_config = currrentConfig; //this is the first config of the slice, in the case of back shooting, make sure to overwrite this with the final config.  
	
	dynamics& localDynamics = m_dynamics();
	
	if (first)
	{
		//DOES THIS WORK?? DOESN"T WORK FIX THIS!!
		const config& configRef = localDynamics.GetCurrConfig();
		m_firstConfig = configRef;
		localDynamics.m_advanceDynamics(m_timeInterval);
		//LIST STUFF GOES HERE
		m_lastConfig = localDynamics.GetCurrConfig();
	}
	else 
	{
	//	m_lastConfig = m_dynamics().m_getCurrConfig();
		m_dynamics().m_advanceDynamics(m_timeInterval);
		//LIST STUFF GOES HERE
	//	m_firstConfig = m_dynamics().m_getCurrConfig();
	}
}

slice::~slice(){
}

