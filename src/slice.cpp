/*
 *  slice.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 8/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "slice.h"

//slice::slice(){
//}

//make a class called config, config should know it's size TODO, configs should have the list.

slice::slice(dynamics &currentDynamics, bool first, double timeInterval)
:	p_curr_dynamics( &currentDynamics )
{
	//if first = true then we are going "forward" otherwise going backwards. 
//	m_temp = temp;
	m_timeInterval = timeInterval;
//	m_config = currrentConfig; //this is the first config of the slice, in the case of back shooting, make sure to overwrite this with the final config.  
	
	if (first)
	{
		//DOES THIS WORK??
		m_firstConfig = m_dynamics().m_getCurrConfig();
		m_dynamics().m_advanceDynamics(m_timeInterval);
		//LIST STUFF GOES HERE
		m_lastConfig = m_dynamics().m_getCurrConfig();
	}
	else 
	{
		m_lastConfig = m_dynamics().m_getCurrConfig();
		m_dynamics().m_advanceDynamics(m_timeInterval);
		//LIST STUFF GOES HERE
		m_firstConfig = m_dynamics().m_getCurrConfig();
	}
}

slice::~slice(){
}

