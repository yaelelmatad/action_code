/*
 *  dynamics.h
 *  Action
 *
 *  Created by Yael Elmatad on 6/11/12.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef _DYNAMICS_H
#define	_DYNAMICS_H
#define MAXLISTS 15

#include "Constants.h"


// forward declarations
class Config;
class Input;

class Dynamics{
public:

    Dynamics( const Input &); //overloaded constructor
	
	void	UpdateConfigBlock( Config*, double interval ) const;
	//advances a config by an amount "interval"
	double	UpdateConfigOneStep( Config* ) const;
	//does just one stepl returns the time increment.
	
private:
	
	void 	PickAndFlipSpin( Config& toUpdate, double totalRate ) const;
	void 	InitializeRates();
	double 	GetTotalRate( const Config& localConfig ) const;
	
	// Data members
	double m_temp;
	double m_cprob; //exp(-1/T)
	double m_epsilon;
	double m_leftRate;
	double m_rightRate;
	double m_rates[MAXLISTS]; //keeps individual rates for easy updating (for one of such process)

	//void m_advanceDynamics(double);
	// to be called by other classes (slice?) to advance dynamics
	double PickATime( double totalRate ) const;
	
	friend class Slice;
	friend class Config;
};

#endif /*_SLICE_H*/
