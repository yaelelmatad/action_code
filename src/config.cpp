/*
 *  config.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 8/16/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "config.h"

/*config::config(){
}*/

config::config(){

}

config::config(config currentConfig()) //constructor if you already have a config and just want to make a new instace
{
	m_length = currentConfig().m_length;
	//COPY an old config to a new one? including the lists. 
}

config::config(double density, int length)
{
	m_density = density;
	m_length = length;
	int size = length*length;
	for (int i=0; i< size; i++)
	{
		m_config[i]=-1;
	//	cout << i << m_config[i] << "\n";
	}
	
	int totalUp = (int)(density*(double)m_length*(double)m_length);
	
	int spinToFlip = rand()%(m_length*m_length);
	m_config[spinToFlip] = 1;
	
	spinToFlip = rand()%(m_length*m_length);
	for (int j = 1; j<totalUp; j++)
	{
		while(m_config[spinToFlip] == 1)
		{
			spinToFlip = rand()%(m_length*m_length);
		}
		m_config[spinToFlip] = 1;
	}
	
	//just a silly check
	for (int i=0; i< length; i++)
	{
		for (int j=0; j<length; j++)
		{
			cout << (m_config[i*length+j]+1)/2 << " ";
		}
		cout << endl;
	}
	
	//make a constructor here that sets up a random config and makes the lists  1D arrays are best. a number of lists feature would be nice too
	//don't forget to put trapped sites on a 0th list
}

config::~config(){
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