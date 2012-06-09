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

slice::slice(config m_config(), double deltaT, double temp, bool direction, double J)
{
	m_temp = temp;
	m_deltaT = deltaT;
//	m_config = currrentConfig; //this is the first config of the slice, in the case of back shooting, make sure to overwrite this with the final config.  
	m_J = J;
	m_dir = direction;  //1 = forward, //0 = backward
}

slice::~slice(){
}

