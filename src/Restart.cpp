/*
 *  restart.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 7/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Restart.h"

Restart::Restart()
{
}

void Restart::PrintRestartFile(int myRank, int randSeed, int index, double currS, Input &currInput, Trajectory &currTraj) const
{
		//store trajectory every StoreFrequency amount of trajecotry for restarts
	//line 1 = index of trajectory
	//line 2 = idum (random number genteartor seed)
	//next nSlices+1 lines = lattice of slices with each line representing one slice
	//next nSlices+1 lines = actionaccum array (1-4) 
	//[1]=Number of faciliated 0->1 flips
	//[2]=Number of fac 1->0 flips
	//[3]=Number of unfac 0->1 flips
	//[4]=Number of unfac 1->0 flips
	//next line is the numbers that go in plistsN[]
	//next 4 lines is the values that go in the arrays plists[][]
	//the next N lines are the backIndexes[][] values  
	char filename[1024];
	sprintf( (char*)filename, "Restart_rank_%d_s_%8.6f_index_%d.dat",myRank, currS, index );
	EraseFile(filename);
	//cout << filename << "\n";
	FILE * fle1;
	fle1 = fopen(filename, "a");
	fprintf(fle1, "%i \n", index);
	fprintf(fle1, "%i \n", randSeed);
	
	currTraj.PrintRestartTraj(fle1);
	/*for (int iSlice=0;iSlice<=nSlices;iSlice++)
	{
		for (int iLattice=1; iLattice<=N; iLattice++)
		{
			fprintf(fle1, "%i ", slices[iLattice][iSlice]);
		}
		fprintf(fle1,"\n");
	}
	for (int iSlice=0;iSlice<nSlices;iSlice++)
		//note, omit nSlicesth slice because it is irrelevent to kink count!!
	{
		//	cout << "kinksUntilSlice[iSlice] " << kinksUntilSlice[iSlice] << "\n";
		for (int iActionAccum=1; iActionAccum<=actionParam; iActionAccum++)
		{
			fprintf(fle1, "%i ", ((int)(actionAccum[iActionAccum][iSlice])));
			//		cout << "actionAccum[i][j] " <<  actionAccum[iActionAccum][iSlice] << "\n";
		}
		fprintf(fle1,"\n");
	}
	//need to preserve list order so that all goes well!!
	for (int ipN = 1; ipN <= nlists; ipN ++) //2/1/09
	{
		fprintf(fle1, "%i ", plistsN[ipN]);
	}
	fprintf(fle1,"\n");
	
	for (int ipN = 1; ipN <= nlists; ipN ++) //2/1/09
	{
		for (int jpN = 1; jpN <= plistsN[ipN]; jpN++)
		{
			fprintf(fle1, "%i ", plists[ipN][jpN]);
		}
	}
	fprintf(fle1,"\n");
	
	for (int iN = 1; iN <= N; iN++)
	{
		fprintf(fle1, "%i %i %i \n", iN, backIndexes[iN][1], backIndexes[iN][2]);
	}*/
	fclose(fle1);
	return;
	 
}


void Restart::EraseFile(char *fle) const
//erases file pointed to by fle.
{
	FILE * fle1;
	fle1 = fopen(fle, "w");
	fclose(fle1);
}





/*
int Restart::GetIntInput(int indicator) const
{
	return intParams[indicator];
}
 */
/*
double Restart::GetDoubleInput(int indicator) const
{
	return doubleParams[indicator];
}
*/
// static

/*
int Restart::StringToInt(string a)
{
	
	string sN_SITES_SUB ("N_SITES_SUB");
	
	/////////////////////////
	
	//this is a macro, passing it a string returns the enum
#define MATCH_STRING_TO_ENUM( __StringName__ ) \
else if( a.compare( #__StringName__ )==0){ return __StringName__; }
	
	//first one has the if statement (no macro)
	if (a.compare(sN_SITES_SUB)==0)
	{
		return N_SITES_SUB;
		
	}
	MATCH_STRING_TO_ENUM( N_SITES_FULL )
	MATCH_STRING_TO_ENUM( N_TRAJS )
	MATCH_STRING_TO_ENUM( N_SLICES )
	MATCH_STRING_TO_ENUM( N_SLICES_SHIFT )
	MATCH_STRING_TO_ENUM( N_STORAGEFREQ )
	MATCH_STRING_TO_ENUM( N_DIMENSION )
	MATCH_STRING_TO_ENUM( N_HARD )
	
	MATCH_STRING_TO_ENUM( D_TEMP )
	MATCH_STRING_TO_ENUM( D_DENSITY )
	MATCH_STRING_TO_ENUM( D_TOBS )
	MATCH_STRING_TO_ENUM( D_START_S )
	MATCH_STRING_TO_ENUM( D_END_S )
	MATCH_STRING_TO_ENUM( D_S_INC )
	MATCH_STRING_TO_ENUM( D_RATE_LEFT )
	MATCH_STRING_TO_ENUM( D_RATE_RIGHT )
	MATCH_STRING_TO_ENUM( D_U )
	MATCH_STRING_TO_ENUM( D_DIFF_RATE )
	MATCH_STRING_TO_ENUM( D_SHOOT_FRACTION )
	else 
	{
		cout << "INVALID INPUT" << endl;
		return -1;
	}
	
}
*/

