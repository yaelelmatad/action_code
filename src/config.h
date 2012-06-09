/*
 *  config.h
 *  Action
 *
 *  Created by Yael Elmatad on 8/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _CONFIG_H
#define	_CONFIG_H
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

#define MAXSIZE 1000000
#define UP 1
#define DOWN -1

using namespace std;

class config {
public:
	config(); //default constr.
    config(config()); //overloaded const
    config(double, int ); //overloaded constructor
    virtual ~config(); //destructor
	//some getters and setters
    //void setInfo(int _old, int _new,long currStep);

	//public variables
	//long int idum=-1; 
	
private:
	//functions
	//float ran2;
	//member variables
	double m_density;
	int m_length;
	int m_config[MAXSIZE]; 
	//config array, starts and 0 and goes to length^2
};

#endif /*_CONFIG_H*/