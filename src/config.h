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

#define MAXSIZE 10000
#define NUM_LISTS 8 
//hardcoded for now
#define UP 1
#define DOWN 0
#define LEFT -1
#define RIGHT 1
#define NOTFACDOWN 0
#define NOTFACUP 1
#define FACLEFTDOWN 2
#define FACLEFTUP 3
#define FACRIGHTDOWN 4
#define FACRIGHTUP 5
#define FACBOTHDOWN 6
#define FACBOTHUP 7
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
	
	void m_checkListIntegrity();
	//makes sure the list integrity is kept. don't use except to check list dynamcis working properly.
	
	void m_moveToList(int spin, int type);
	//moves spin to list of type.  removes it form old list and fills its old spot with last member of that list
	//updates the back indexes of that second spin accordingly.
	
	void m_addToList(int spin, int type);
	//adds spin to list type at the end of the list.  adds +1 to the number of members of the list.


	friend class dynamics;

};


#endif /*_CONFIG_H*/