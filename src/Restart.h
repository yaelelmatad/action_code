/*
 *  restart.h
 *  Action
 *
 *  Created by Yael Elmatad on 7/2012
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef _RESTART_H
#define	_RESTART_H

#include <string>
#include "Constants.h"

// forward declarations
class Input;
class Trajectory;
class TPS;

using namespace std;

class Restart{
public:
	Restart(); //overloaded const
	void PrintRestartFile(int myRank, int myCommSz, int randSeed, int index, double currS, Input &currInput, Trajectory &currTraj) const;
	bool properlyRestarted(char* restartFile, int launched_comm_sz) ;
	int getOldCommSz() const;
	int GetIndex() const;
	int GetRandomSeed() const;
	void LoadRestart(Input & myInput, Trajectory &myTraj, TPS &myTPS, char* restartFile, int my_rank, int comm_sz);
	
	int m_restartedCommSz;
	
private:
	
	static int
	StringToInt( const string& a);
	void EraseFile( const char* filename) const;

	// data members
	int m_randSeed;
	int m_index;
	double m_currS;
		
	//config array, starts and 0 and goes to length^2
};

#endif /*_RESTART_H*/
