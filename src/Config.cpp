/*
 *  config.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 8/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

// Header
#include "Config.h"

// Other includes
#include <stdlib.h>
#include <math.h>
#include <time.h>
// #include <float.h>
#include <iostream>
#include <fstream>
// #include <vector>
#include <string>
#include <sstream>

Config::Config(){

}

Config::Config( const Input &myInput)
{
	m_density = myInput.GetDoubleInput(D_DENSITY);
	m_length = myInput.GetIntInput(N_SITES_FULL);
	//int size = length*length;
	int size = m_length; //lets just stick to one d, K?
	for (int i=0; i< size; i++)
	{
		m_cell[i]=UNOCCUPIED;
	//	cout << i << m_cell[i] << "\n";
	}

	m_clearLists();

	int totalUp = (int)(m_density*(double)m_length);

	int spinToFlip = rand()%(m_length);
	m_cell[spinToFlip] = OCCUPIED;

	spinToFlip = rand()%(m_length);
	for (int j = 1; j<totalUp; j++)
	{
		while(m_cell[spinToFlip] == OCCUPIED)
		{
			spinToFlip = rand()%(m_length);
		}
		m_cell[spinToFlip] = OCCUPIED;
	}

	for (int i = 0; i < m_length; i++)
		m_addToList(i, m_typeOfSpin(i));

	//just some silly checks

	/*
	for (int j=0; j<length; j++)
	{
		cout << m_cell[j] << " " << m_typeOfSpin(j) <<endl;
	}
	 */

	CheckListIntegrity();

	//make a constructor here that sets up a random config and makes the lists  1D arrays are best. a number of lists feature would be nice too
	//don't forget to put trapped sites on a 0th list
}

void Config::m_clearLists()
{
	for (int i = 0; i<=NUM_LISTS; i++)
	{
		m_lists[i][0]=0;
	}
	return;
}

void Config::CheckListIntegrity()
{ 
	//first check back indexes
	for (int i = 0; i< m_length; i++)
	{
		if (m_lists[m_locationOfSpinOnLists[i][0]][m_locationOfSpinOnLists[i][1]]!=i)
		{
			cout << "list broken for spin " << i << endl;
			cout << "m_locationOfSpinOnLists["<<i<<"][0] = " << m_locationOfSpinOnLists[i][0] << endl;
			cout << "m_locationOfSpinOnLists["<<i<<"][1] = " << m_locationOfSpinOnLists[i][1] << endl;
			cout << "m_lists in that location = " << m_lists[m_locationOfSpinOnLists[i][0]][m_locationOfSpinOnLists[i][1]] << endl;
			cout << "Type of Spin is " << m_typeOfSpin(i) << endl;
		}

		if (m_typeOfSpin(i) != m_locationOfSpinOnLists[i][0])
		{
			cout << "spin on wrong list!" << endl;
			cout << "spin " << i << " should be on list " << m_typeOfSpin(i) << endl;
			cout << "actually on list " << m_locationOfSpinOnLists[i][0] << endl;
			cout << "Left Neighbor " << m_cell[m_neighbor(i, -1)] << endl;
			cout << "i State " << m_cell[i] << endl;
			cout << "Right Neighbor " << m_cell[m_neighbor(i, 1)] << endl;
		}
	}

	//second check forward indexing
	for (int i = 0; i< NUM_LISTS; i++)
	{
		for (int j = 1; j <= m_lists[i][0]; j++)
		{
			if (m_locationOfSpinOnLists[m_lists[i][j]][0]!= i || m_locationOfSpinOnLists[m_lists[i][j]][1] != j)
			{
				cout << "list broken for site on m_lists " << i <<"," << j << endl;
				cout << "m_lists["<<i<<"]["<<j<<"] = " << m_lists[i][j] << endl;
				cout << "m_locationOfSpinOnLists["<<i<<"][1] = " << m_locationOfSpinOnLists[i][1] << endl;
				cout << "m_locationOfSpinOnLists["<<i<<"][0] = " << m_locationOfSpinOnLists[i][0] << endl;
				cout << "Type of Spin is " << m_typeOfSpin(i) << endl;

			}
		}
	}

}

int Config::m_neighbor(int spin, int dir)
{
	if (dir == LEFT && spin == 0)
		return m_length-1;
	else if (dir == RIGHT && spin == m_length-1)
		return 0;
	else 
		return (spin + dir);
	//fix this!
}

void Config::m_flipSpin(int spin)
{
	int leftNeighbor =m_neighbor(spin, LEFT);
	int rightNeighbor = m_neighbor(spin, RIGHT);
	m_cell[spin] = abs(m_cell[spin]-1); //0->1 and 1->0
	m_moveToList(spin,m_typeOfSpin(spin));
	m_moveToList(leftNeighbor,m_typeOfSpin(leftNeighbor));
	m_moveToList(rightNeighbor,m_typeOfSpin(rightNeighbor));


	return;
}

void Config::PrintRestartConfig(FILE* outputFile, int index) const
{
	fprintf(outputFile, "%i ", index);
	for (int iLattice=0; iLattice<m_length; iLattice++)
	{
		fprintf(outputFile, "%i ", m_cell[iLattice]);
	}
	fprintf(outputFile,"\n");
	
	//print list numbers
	fprintf(outputFile, "%i ", index);
	for (int iLists=0; iLists < NUM_LISTS;iLists++)
	{
		fprintf(outputFile, "%i ", m_lists[iLists][0]);
	}
	fprintf(outputFile, "\n");
	
	for (int iLists = 0; iLists<NUM_LISTS; iLists++)
	{
		fprintf(outputFile, "%i ", index);
		for (int iOnList = 1; iOnList <=m_lists[iLists][0]; iOnList++)
		{
			fprintf(outputFile, "%i ", m_lists[iLists][iOnList]);
		}
		fprintf(outputFile, "\n");
	}
	
	//print backindexes
	for (int iSpin = 0; iSpin< m_length; iSpin++)
	{
		fprintf(outputFile, "%i ", index);
		fprintf(outputFile, "%i %i \n", m_locationOfSpinOnLists[iSpin][0], m_locationOfSpinOnLists[iSpin][1]);
	}
	
}


void Config::LoadRestartConfig(FILE* inputFile, int index) 
{
	fscanf(inputFile, "%i ", &index);
	for (int iLattice=0; iLattice<m_length; iLattice++)
	{
		fscanf(inputFile, "%i ", &(m_cell[iLattice]));
		cout <<"m_cell " << iLattice << " = " << m_cell[iLattice] << endl;;
	}
	cout << endl;
	fscanf(inputFile,"\n");
	
	//print list numbers
	fscanf(inputFile, "%i ", &index);
	for (int iLists=0; iLists < NUM_LISTS;iLists++)
	{
		fscanf(inputFile, "%i ", &(m_lists[iLists][0]));
	}
	fscanf(inputFile, "\n");
	
	for (int iLists = 0; iLists<NUM_LISTS; iLists++)
	{
		fscanf(inputFile, "%i ", &index);
		for (int iOnList = 1; iOnList <=m_lists[iLists][0]; iOnList++)
		{
			fscanf(inputFile, "%i ", &(m_lists[iLists][iOnList]));
		}
		fscanf(inputFile, "\n");
	}
	
	//print backindexes
	for (int iSpin = 0; iSpin< m_length; iSpin++)
	{
		fscanf(inputFile, "%i ", &index);
		fscanf(inputFile, "%i %i \n", &m_locationOfSpinOnLists[iSpin][0], &m_locationOfSpinOnLists[iSpin][1]);
	}
	
}




void Config::printConfig(ofstream &outputFile, double time) const
{
	for (int j = 0; j<m_length; j++)
	{	
		if (m_cell[j] == 1)
		{
			outputFile<< time << " " << j << endl;
		}
	}
	return;
}

int Config::getConfig(int spin)
{
	return m_cell[spin];
}

void Config::m_addToList(int spin, int type)
{
	m_lists[type][0]++; //the length of the list grows by one
	m_lists[type][m_lists[type][0]] = spin; //add the spin to that list
	m_locationOfSpinOnLists[spin][0]=type;//which list is spin on
	m_locationOfSpinOnLists[spin][1]=m_lists[type][0]; //location on list.

	/*
	 cout << " spin = " << spin << " of type " << type << endl;
	cout << "m_lists[type][0] now " << m_lists[type][0] << endl;; 
	cout << "m_lists[type][m_lists[type][0]] = " << m_lists[type][m_lists[type][0]] << endl;
	cout << "m_locationOfSpinOnLists[spin][0] = " << type << endl;
	cout << "m_locationOfSpinOnLIsts[spin][1]= " << m_lists[type][0] << endl;
	*/
	 return;
}




void Config::m_moveToList(int spin, int type)
{
	//routine that takes a spin and moves it to the list "type"

	//first remove then add to list
	int oldList = m_locationOfSpinOnLists[spin][0];
	int oldLocation = m_locationOfSpinOnLists[spin][1];

	//move last element of old list to spot where this spin was
	int lastSpin = m_lists[oldList][m_lists[oldList][0]];
	m_lists[oldList][oldLocation] = lastSpin;
	m_lists[oldList][0]--; //one less spin on this list

	//change the backindex (stays on same list but switches location)
	m_locationOfSpinOnLists[lastSpin][1]=oldLocation; 

	//finally add the original spin to it's new list.
	m_addToList(spin, type);
	return;
}

int Config::m_typeOfSpin(int spin)
{
	//returns the "type" of spin for listing
	//here is very MODEL specific.

	int leftNeigh = m_cell[m_neighbor(spin, LEFT)];
	int rightNeigh = m_cell[m_neighbor(spin, RIGHT)];

	if (m_cell[spin]==UNOCCUPIED)
	{												
		if (leftNeigh == OCCUPIED && rightNeigh == OCCUPIED)
		{
			return FACBOTHDOWN;
		}				  
		else if (leftNeigh == OCCUPIED)
		{
			return FACLEFTDOWN;
		}		
		else if (rightNeigh == OCCUPIED)
		{
			return FACRIGHTDOWN;			  
		}
		else
		{
			return NOTFACDOWN;
		}
	}							  
	else
	{												
		if (leftNeigh == OCCUPIED && rightNeigh == OCCUPIED)
		{
			return FACBOTHUP;
		}				  
		else if (leftNeigh == OCCUPIED)
		{
			return FACLEFTUP;
		}		
		else if (rightNeigh == OCCUPIED)
		{
			return FACRIGHTUP;			  
		}
		else
		{
			return NOTFACUP;
		}
	}						  

}

void Config::PrintDynamicsCells() const
{
	for (int i = 0; i< m_length; i++)
	{
		cout << m_cell[i] << " ";
	}
}

/*

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

float ran2(long *idum){
  int j;
  long k;
  static long idum2=123456789;
  static long iy=0;
  static long iv[NTAB];
  float temp;
  if (*idum <= 0) {
    if (-(*idum) < 1) *idum=1;
    else *idum = -(*idum);
    idum2 = (*idum);
    for (j=NTAB+7;j>=0;j--) {
     k=(*idum)/IQ1;
      *idum=IA1*(*idum-k*IQ1)-k*IR1;
      if (*idum < 0) *idum += IM1;
      if (j < NTAB) iv[j] = *idum;
    }
    iy=iv[0];
  }
  k=(*idum)/IQ1;
  *idum=IA1*(*idum-k*IQ1)-k*IR1;
  if (*idum < 0) *idum += IM1;
  k=idum2/IQ2;
  idum2=IA2*(idum2-k*IQ2)-k*IR2;
  if (idum2 < 0) idum2 += IM2;
  j=iy/NDIV;
  iy=iv[j]-idum2;
  iv[j] = *idum;
  if (iy < 1) iy+= IMM1;
  if ((temp=AM*iy) > RNMX) return RNMX;
  else return temp;
}

*/
