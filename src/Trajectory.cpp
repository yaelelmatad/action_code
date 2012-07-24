/*
 *  Trajectory.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 06/2012
 *  Copyright 2012. All rights reserved.
 *
 */

#include "Trajectory.h"

Trajectory::Trajectory(){
}

Trajectory::Trajectory( const Input &myInput, Direction direction)
{
	
	

	//constructor that makes a FULL trajectory
	//must be submitted via input!
	m_n_slices = myInput.GetIntInput(N_SLICES);
	m_n_slices_full = m_n_slices;
	m_tObs = myInput.GetDoubleInput(D_TOBS);
	m_traj.resize(m_n_slices);
	Config myConfig(myInput);
	int i;
	
	//Direction direction = EDirection_BACKWARD;
	if (direction == EDirection_FORWARD)
		i = 0;
	
	if (direction == EDirection_BACKWARD)
		i=m_n_slices-1;
	
	m_traj[i] = Slice(myInput, myConfig, direction );

	for (i+=direction; i < m_n_slices && i >= 0; i+=direction)
	{
		m_traj[i] = Slice(myInput, m_traj[i-direction].GetSeedConfig( direction ), direction );
	}
	
	//printTrajectory(11);
	
}

Trajectory::Trajectory( const Input &myInput, const Config &myConfig, Direction direction, int n_slicesSnip)
{
	//constructor capable of making a snippet from a seed config.
	m_n_slices = n_slicesSnip;
	m_n_slices_full = myInput.GetIntInput(N_SLICES);
	m_tObs = myInput.GetDoubleInput(D_TOBS);
	m_traj.resize(m_n_slices);
	//Config myConfig(myInput);
	int i;
	
	//Direction direction = EDirection_BACKWARD;
	if (direction == EDirection_FORWARD)
		i = 0;
	
	if (direction == EDirection_BACKWARD)
		i=m_n_slices-1;
	
	m_traj[i] = Slice(myInput, myConfig, direction );
	for (i+=direction; i < m_n_slices && i >= 0; i+=direction)
	{
		m_traj[i] = Slice(myInput, m_traj[i-direction].GetSeedConfig( direction ), direction );
	}
	
}


int Trajectory::GetOrderParameter(int firstSlice, int lastSlice) const
{
	int orderParam = 0;
	for (int i = firstSlice; i<=lastSlice; i++)
	{
		orderParam+=m_traj[i].GetOrderParam();
	}
	
	return orderParam;
}

void Trajectory::MergeTrajectories(const Trajectory &snippet, int firstSliceToErase, int lastSliceToErase, Side currSide, Direction currDir)
{
	//currDir might be unnecessary?
	//suspect that when currSide = back then currDir always  = forwards
	//and when currSide = front then currDir = backwards
	//think about this?
	deque<Slice>::iterator iter1 = m_traj.begin() + firstSliceToErase;
	deque<Slice>::iterator iter2 = m_traj.begin() + lastSliceToErase + 1;
	m_traj.erase(iter1, iter2);
	//erases [first,last) (so need to +1 to truly erase "last")
	
	int sizeOfSnippet = snippet.getLengthOfTraj();
	/*
	int sizeOfRemainingTraj = m_traj.size();
	int currDirBinary = -1*(currDir-1)/2; //backwards now equals 1 and forwards 0
	 */
	
	if (currSide == ESide_END)
	{//add to end
		
		for (int i = 0;i < sizeOfSnippet; i++)
		{
			m_traj.push_back(snippet.GetSlice(i));
		}
		
	}
	else //adding to beginning
	{
	
		for (int i=sizeOfSnippet-1;i >=0; i--)
		{
			m_traj.push_front(snippet.GetSlice(i));
		}
	//add to beginning
	}


}



const Slice& Trajectory::GetSlice(int indicator) const
{
	return m_traj[indicator];

}

int Trajectory::getLengthOfTraj() const
{
	return m_traj.size();
}

void Trajectory::PrintRestartTraj(FILE* outputFile) const
{
	for (int i = 0; i < m_n_slices; i++)
	{
		m_traj[i].PrintRestartSlice(outputFile, i);
	}
}


void Trajectory::LoadRestartTraj(FILE* inputFile) 
{
	for (int i = 0; i < m_n_slices; i++)
	{
		m_traj[i].LoadRestartSlice(inputFile, i);
	}
}


void Trajectory::PrintOrderParameter(double param) const
{

	char filename[1024];
	sprintf( (char*)filename, "OrderP_param_%lf.dat", param );
	FILE * fle1;
	fle1 = fopen(filename, "a");
	
	double orderP = 0;
	for (int i =0; i<m_n_slices;i++)
	{
		orderP += m_traj[i].GetOrderParamDouble();
	}
	
	fprintf(fle1, "%lf \n", orderP);

	fclose(fle1);
}

void Trajectory::EraseOrderParameterFile(double param) const
{
	char filename[1024];
	sprintf( (char*)filename, "OrderP_param_%lf.dat", param );
	EraseFile(filename);
	
}

void Trajectory::EraseFile(char *fle) const
//erases file pointed to by fle.
{
	FILE * fle1;
	fle1 = fopen(fle, "w");
	fclose(fle1);
}



void Trajectory::printTrajectory(int rank, int indicator, double param) const
{
	double interval = m_tObs/m_n_slices_full;
	double time = 0;
	//Config currConfig;
	string filename ("traj_i_");
	std::ostringstream oss;
	oss << indicator;
	filename += oss.str();
	filename += "_rank_";
	std::ostringstream oss2;
	oss2 << rank;
	filename += oss2.str();
	filename += "_param_";
	std::ostringstream oss3;
	oss3 << param;
	filename += oss3.str();
	filename += ".dat";

	
	//cout << "m_n_slices = " << m_n_slices << endl;

	//cout << filename << endl;
	
	ofstream outputFile;
	outputFile.open(filename.c_str());
	
	//pass to slice which passes to config (slice and traj therefore don't need to know how a config "looks", just pass the time along
	for (int i = 0; i < m_n_slices; i++)
	{
		m_traj[i].printFirstConfig(outputFile, time);				
		time += interval;
	}

	m_traj[m_n_slices-1].printLastConfig(outputFile, time);				
}



Trajectory::~Trajectory(){	
}

