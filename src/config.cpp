/*
 *  config.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 8/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "config.h"

config::config(){

}

config::config(double density, int length)
{
	m_density = density;
	m_length = length;
	//int size = length*length;
	int size = length; //lets just stick to one d, K?
	for (int i=0; i< size; i++)
	{
		m_config[i]=UNOCCUPIED;
	//	cout << i << m_config[i] << "\n";
	}

	m_clearLists();

	int totalUp = (int)(density*(double)m_length);

	int spinToFlip = rand()%(m_length);
	m_config[spinToFlip] = OCCUPIED;

	spinToFlip = rand()%(m_length);
	for (int j = 1; j<totalUp; j++)
	{
		while(m_config[spinToFlip] == OCCUPIED)
		{
			spinToFlip = rand()%(m_length);
		}
		m_config[spinToFlip] = OCCUPIED;
	}

	for (int i = 0; i < m_length; i++)
		m_addToList(i, m_typeOfSpin(i));

	//just some silly checks

	/*
	for (int j=0; j<length; j++)
	{
		cout << m_config[j] << " " << m_typeOfSpin(j) <<endl;
	}
	 */

	m_checkListIntegrity();

	//make a constructor here that sets up a random config and makes the lists  1D arrays are best. a number of lists feature would be nice too
	//don't forget to put trapped sites on a 0th list
}

void config::m_clearLists()
{
	for (int i = 0; i<=NUM_LISTS; i++)
	{
		m_lists[i][0]=0;
	}
	return;
}

void config::m_checkListIntegrity()
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
			cout << "spin " << i << "should be on list " << m_typeOfSpin(i) << endl;
			cout << "actually on list " << m_locationOfSpinOnLists[i][0] << endl;
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

int config::m_neighbor(int spin, int dir)
{
	if (dir == LEFT && spin == 0)
		return m_length-1;
	else if (dir == RIGHT && spin == m_length-1)
		return 0;
	else 
		return (spin + dir);
	//fix this!
}

void config::m_flipSpin(int spin)
{
	m_config[spin] = abs(m_config[spin]-1); //0->1 and 1->0
	m_moveToList(spin,m_typeOfSpin(spin));
	m_moveToList(spin,m_neighbor(spin, LEFT));
	m_moveToList(spin,m_neighbor(spin, RIGHT));

	return;
}


void config::m_addToList(int spin, int type)
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

void config::m_moveToList(int spin, int type)
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

int config::m_typeOfSpin(int spin)
{
	//returns the "type" of spin for listing
	//here is very MODEL specific.

	int leftNeigh = m_config[m_neighbor(spin, LEFT)];
	int rightNeigh = m_config[m_neighbor(spin, RIGHT)];

	if (m_config[spin]==UNOCCUPIED)
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
