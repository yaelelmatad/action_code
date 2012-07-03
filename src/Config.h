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
// #include <float.h>
#include <iostream>
#include <fstream>
// #include <vector>
#include <string>
#include <sstream>

#define MAXSIZE 10000
#define NUM_LISTS 8 
//hardcoded for now


#include "Input.h"

enum OccState
{
	UNOCCUPIED = 0,
	OCCUPIED = 1
};

enum Lateral
{
	LEFT = -1,
	RIGHT = 1
};

enum SpinCategories
{
	NOTFACDOWN, //0
	NOTFACUP,  //1
	FACLEFTDOWN, //2
	FACLEFTUP, //3
	FACRIGHTDOWN, //4 
	FACRIGHTUP, //5 
	FACBOTHDOWN, //6
	FACBOTHUP //7
};

using namespace std;

class Config {
public:
	Config(); //default constr.
    Config( const Input &); //overloaded constructor

	void PrintRestartConfig(FILE* outputFile, int index) const;
	void printConfig(ofstream &outputFile, double time) const;
	//some getters and setters
	int getConfig(int spin);
	
private:
	//functions
	//float ran2;
	//member variables
	double m_density;
	int m_length;
	int m_cell[MAXSIZE];
	//config array, starts and 0 and goes to length
	int m_locationOfSpinOnLists[MAXSIZE][2];
	//1st one tells you WHICH list 2nd one tells you which position
	int m_lists[NUM_LISTS][MAXSIZE];
	//m_lists[1][0] tells you size of list 1
	//m-lists[1][1] (etc) is first object in that list
	
	void m_clearLists();
	//sets all m_lists[i][0]=0;
	
	int m_typeOfSpin(int );
	//returns the type of spin o the variable passed to it.
	
	int m_neighbor(int, int);
	//first argument is the spin to which you want ot find neighbors
	//takes care of periodic boundaries
	//returns left neighbor if seonc variable = left
	//returns right neighbor if second variable = right
	
	void CheckListIntegrity();
	//makes sure the list integrity is kept. don't use except to check list dynamcis working properly.
	
	void m_moveToList(int spin, int type);
	//moves spin to list of type.  removes it form old list and fills its old spot with last member of that list
	//updates the back indexes of that second spin accordingly.
	
	void m_addToList(int spin, int type);
	//adds spin to list type at the end of the list.  adds +1 to the number of members of the list.

	void m_flipSpin(int spin);
	//flips spin as well as moves it to proper list (also for neighbors)

	friend class Dynamics;

};


#endif /*_CONFIG_H*/
