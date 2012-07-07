/*
  *  slice.h
  *  Action
  *
  *  Created by Yael Elmatad on 8/16/10.
  *  Copyright 2010 __MyCompanyName__. All rights reserved.
  *
  */


#ifndef _SLICE_H
#define	_SLICE_H
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
#include "Dynamics.h"
#include "Input.h"

#define MAXSIZE 10000
/*enum OccState
 {
 OCCUPIED,
 UNOCCUPIED,
 };*/

using namespace std;

enum Direction
{
	EDirection_FORWARD = 1,
	EDirection_BACKWARD = -1
};

class Slice{
public:
    Slice(); //overloaded const
    Slice( const Input &, const Config &, Direction ); //overloaded constructor
	const Config& GetFirstConfig() const;
	const Config& GetLastConfig() const;
	const Config& GetSeedConfig(Direction) const;
	void PrintRestartSlice(FILE* outputFile, int index) const;
	void LoadRestartSlice(FILE* inputFile, int index);
	void printLastConfig(ofstream &outputFile, double time) const;
	void printFirstConfig(ofstream &outputFile, double time) const;
    virtual ~Slice(); //destructor
	int GetOrderParam() const;
	double GetOrderParamDouble() const;

	
private:
	//functions
	//member variables
	double m_timeInterval;
	bool m_first;
	int m_K; //Kinks
	
	void UpdateConfig(const Dynamics& currDynamics, Config& confToUpdate, double interval);
	void UpdateActionParameters();
	
	Config m_firstConfig; //first is the one that is the last config in that slice TIME WISE (with earlier time)
	Config m_lastConfig; //last is the last one in that slice TIME WISE
	
	friend class Dynamics;
	
	//config array, starts and 0 and goes to length^2
};

#endif /*_SLICE_H*/
