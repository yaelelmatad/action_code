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
	//constructor routine that takes in an imput file and randomly creates a configuration
	
	//get input from myInput
	m_density = myInput.GetDoubleInput(D_DENSITY);
	m_length = myInput.GetIntInput(N_SITES_FULL);
	
	//currently set up for 1d configs
	int size = m_length; 
	
	//clears out the cell array
	for (int i=0; i< size; i++)
	{
		m_cell[i]=UNOCCUPIED;
	}

	//clears out the rate lists
	ClearLists();

	//takes the input density to figure out how many "occupied" sites to add and "floors" this fn by casting as int
	int totalUp = (int)(m_density*(double)m_length);

	int spinToFlip = rand()%(m_length);
	
	m_cell[spinToFlip] = OCCUPIED;
	spinToFlip = rand()%(m_length);

	for (int j = 1; j<totalUp; j++)
	{
		while(m_cell[spinToFlip] == OCCUPIED) //need to make sure that currently chosen site isn't already occupied
		{
			spinToFlip = rand()%(m_length);
		}
		m_cell[spinToFlip] = OCCUPIED;
	}

	for (int i = 0; i < m_length; i++)  //set up the lists
		AddToList(i, TypeOfSpin(i));


	//CheckListIntegrity(); //commented out now but can be reinserted for checking.

}

void Config::ClearLists()
{
	//routine that just clears out the neighbor lists
	for (int i = 0; i<NUM_LISTS; i++)
	{
		m_lists[i][0]=0;
	}
	return;
}

void Config::CheckListIntegrity()
{ 
	//this routine just checks that the spin are all on the proper list and that the backindexes point to the proper location
	
	//first check back indexes
	for (int i = 0; i< m_length; i++)
	{
		if (m_lists[m_locationOfSpinOnLists[i][0]][m_locationOfSpinOnLists[i][1]]!=i)
		{
			cout << "list broken for spin " << i << endl;
			cout << "m_locationOfSpinOnLists["<<i<<"][0] = " << m_locationOfSpinOnLists[i][0] << endl;
			cout << "m_locationOfSpinOnLists["<<i<<"][1] = " << m_locationOfSpinOnLists[i][1] << endl;
			cout << "m_lists in that location = " << m_lists[m_locationOfSpinOnLists[i][0]][m_locationOfSpinOnLists[i][1]] << endl;
			cout << "Type of Spin is " << TypeOfSpin(i) << endl;
		}

		if (TypeOfSpin(i) != m_locationOfSpinOnLists[i][0])
		{
			cout << "spin on wrong list!" << endl;
			cout << "spin " << i << " should be on list " << TypeOfSpin(i) << endl;
			cout << "actually on list " << m_locationOfSpinOnLists[i][0] << endl;
			cout << "Left Neighbor " << m_cell[Neighbor(i, -1)] << endl;
			cout << "i State " << m_cell[i] << endl;
			cout << "Right Neighbor " << m_cell[Neighbor(i, 1)] << endl;
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
				cout << "Type of Spin is " << TypeOfSpin(i) << endl;

			}
		}
	}

}

int Config::Neighbor(int spin, int dir)
{
	//gets the neigbhor of a spin.  dir -1 = "left" neighbor, dir = +1 = right neighbor
	
	if (dir == LEFT && spin == 0)
		return m_length-1;
	else if (dir == RIGHT && spin == m_length-1)
		return 0;
	else 
		return (spin + dir);
}

void Config::FlipSpin(int spin)
{
	
	//flips the state of the spin and deals with list
	//need to move the left/right neighbor to their proper lists
	
	//get neighbors
	int leftNeighbor =Neighbor(spin, LEFT);
	int rightNeighbor = Neighbor(spin, RIGHT);
	
	//flip spin
	m_cell[spin] = abs(m_cell[spin]-1); //0->1 and 1->0
	
	//move the spin and spin +/- 1 to proper lists
	MoveToList(spin,TypeOfSpin(spin));
	MoveToList(leftNeighbor,TypeOfSpin(leftNeighbor));
	MoveToList(rightNeighbor,TypeOfSpin(rightNeighbor));


	return;
}

void Config::PrintRestartConfig(FILE* outputFile, int index) const
{
	//prints formatted restart data to outputFile 
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


void Config::LoadRestartConfig(FILE* restartFile) 
{
	int index; //just a temporary variable for reading in the file (lines start with slice index)
	
	fscanf(restartFile, "%i ", &index);
	for (int iLattice=0; iLattice<m_length; iLattice++) //reads in the formatted config 
	{
		fscanf(restartFile, "%i ", &(m_cell[iLattice]));
	//	cout <<"m_cell " << iLattice << " = " << m_cell[iLattice] << endl;;
	}
	//cout << endl;
	fscanf(restartFile,"\n");
	
	//loads list numbers
	fscanf(restartFile, "%i ", &index);
	for (int iLists=0; iLists < NUM_LISTS;iLists++)
	{
		fscanf(restartFile, "%i ", &(m_lists[iLists][0]));
	}
	fscanf(restartFile, "\n");
	
	for (int iLists = 0; iLists<NUM_LISTS; iLists++)
	{
		fscanf(restartFile, "%i ", &index);
		for (int iOnList = 1; iOnList <=m_lists[iLists][0]; iOnList++)
		{
			fscanf(restartFile, "%i ", &(m_lists[iLists][iOnList]));
		}
		fscanf(restartFile, "\n");
	}
	
	//loads backindexes
	for (int iSpin = 0; iSpin< m_length; iSpin++)
	{
		fscanf(restartFile, "%i ", &index);
		fscanf(restartFile, "%i %i \n", &m_locationOfSpinOnLists[iSpin][0], &m_locationOfSpinOnLists[iSpin][1]);
	}
	
}




void Config::PrintConfig(ofstream &outputFile, double time) const
{
	//prints the config to an outputFile along with the current time
	//formatted for gnuplot
	for (int j = 0; j<m_length; j++)
	{	
		if (m_cell[j] == 1)
		{
			outputFile<< time << " " << j << endl;
		}
	}
	return;
}

int Config::GetConfig(int spin)
{
	//returns the value of the m_cell at spin 
	return m_cell[spin];
}

void Config::AddToList(int spin, int type)
{
	//ads spin to the list indicated by type.  increments list, and takes care of backindexes
	m_lists[type][0]++; //the length of the list grows by one
	m_lists[type][m_lists[type][0]] = spin; //add the spin to that list
	m_locationOfSpinOnLists[spin][0]=type;//which list is spin on
	m_locationOfSpinOnLists[spin][1]=m_lists[type][0]; //location on list.

	 return;
}




void Config::MoveToList(int spin, int type)
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
	AddToList(spin, type);
	return;
}

int Config::TypeOfSpin(int spin)
{
	//returns the "type" of spin for listing
	//here is very MODEL specific.

	int leftNeigh = m_cell[Neighbor(spin, LEFT)];
	int rightNeigh = m_cell[Neighbor(spin, RIGHT)];

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
