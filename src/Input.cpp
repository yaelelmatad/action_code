/*
 *  input.cpp
 *  Action
 *
 *  Created by Yael Elmatad on 6/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Input.h"

//Input::Input(){
//}

//make a class called config, config should know it's size TODO, configs should have the list.

Input::Input(char* in, int myRank)
{
	//reads the input file
	string line;
	string value; // to get first element
	string name_of_value;
	string type_of_value;
	string intChar ("N");
	string doubleChar ("D");
	int indicator;
	
	for (int i = 0 ; i < MAXARGS; i++)
	{ //unitilizaed values get -1
		intParams[i]=-1;
		doubleParams[i]=-1;
	}
	if (myRank == 0)
	{
		cout << "Input read with the following parameters;" <<endl;
	}
	
	ifstream inputFile (in); //opens file
	if (inputFile.is_open()) //reads until eof
	{
		getline (inputFile,line);
		do 
		{
		//	cout << line << endl; //gets the line 
			
			istringstream iss(line);
			iss >> value;
			//cout << "Substring: " << value << endl;

			iss >> type_of_value;
			//cout << "Substring: " << type_of_value << endl;
			
			iss >> name_of_value;
			//cout << "Substring: " << name_of_value << endl;
			
			if (intChar.compare(type_of_value)==0)
			{
				//cout << "reading an integer" << endl;
				indicator = stringToInt(name_of_value);
				//cout << indicator << endl;
				if (indicator>-1)
				{
					istringstream (value) >> intParams[indicator]; 
					//cout << intParams[indicator] << endl;
					if (myRank == 0)
						cout << intParams[indicator] << " N " << name_of_value << endl;
				}
			}
			
			if (doubleChar.compare(type_of_value)==0)
			{
				//cout << "reading a double" << endl; 
				indicator = stringToInt(name_of_value);
				//cout << indicator << endl;			
				if (indicator>-1)
				{
					istringstream (value) >> doubleParams[indicator]; 
					//cout << doubleParams[indicator] << endl;
					if (myRank == 0)
						cout << doubleParams[indicator] << " D "<< name_of_value << endl;

				}
			}
			getline (inputFile,line);
		} while( !inputFile.eof() );
		inputFile.close();
	}
	
	else cout << "Unable to open file" << endl; 
	
	
	
}

Input::~Input(){
}


int Input::getIntInput(int indicator) 
{
	return intParams[indicator];
}

double Input::getDoubleInput(int indicator) 
{
	return doubleParams[indicator];
}



int Input::stringToInt(string a) 
{

	string sN_SITES_SUB ("N_SITES_SUB");
	string sN_SITES_FULL("N_SITES_FULL");
	string sN_TRAJS ("N_TRAJS");
	string sN_SLICES ("N_SLICES");
	string sN_SLICES_SHIFT ("N_SLICES_SHIFT");
	string sN_STORAGEFREQ ("N_STORAGEFREQ");
	string sN_DIMENSION ("N_DIMENSION");
	string sN_HARD ("N_HARD");
	
	string sD_TEMP ("D_TEMP");
	string sD_DENSITY ("D_DENSITY");
	string sD_TOBS ("D_TOBS");
	string sD_START_S ("D_START_S");
	string sD_END_S ("D_END_S");
	string sD_S_INC ("D_S_INC");
	string sD_RATE_LEFT ("D_RATE_LEFT");
	string sD_RATE_RIGHT ("D_RATE_RIGHT");
	string sD_U ("D_U");
	string sD_DIFF_RATE ("D_DIFF_RATE");
	
	if (a.compare(sN_SITES_SUB)==0)
	{
		return N_SITES_SUB;
	
	}
	else if (a.compare(sN_SITES_FULL)==0)
	{
		return N_SITES_FULL;
	}
	else if (a.compare(sN_TRAJS)==0)
	{
		return N_TRAJS;
	}
	else if (a.compare(sN_SLICES)==0)
	{
		return N_SLICES;
	}
	else if (a.compare(sN_SLICES_SHIFT)==0)
	{	
		return N_SLICES_SHIFT;
	}
	else if (a.compare(sN_STORAGEFREQ)==0)
	{
		return N_STORAGEFREQ;
	}
	else if (a.compare(sN_DIMENSION)==0)
	{	
		return N_DIMENSION;
	}
	else if (a.compare(sN_HARD)==0)
	{	
		return N_HARD;
	}
	else if (a.compare(sD_TEMP)==0)
	{	
		return D_TEMP;
	}
	else if(a.compare(sD_DENSITY)==0)
	{	
		return D_DENSITY;
	}
	else if(a.compare(sD_TEMP)==0)
	{	
		return D_TEMP;
	}
	else if(a.compare(sD_TOBS)==0)
	{	
		return D_TOBS;
	}
	else if (a.compare(sD_START_S)==0)
	{	
		return D_START_S;
	}
	else if (a.compare(sD_END_S)==0)
	{	
		return D_END_S;}
	else if (a.compare(sD_S_INC)==0)
	{	
		return D_S_INC;}
	else if (a.compare(sD_RATE_LEFT)==0)
	{	
		return D_RATE_LEFT;}
	else if (a.compare(sD_RATE_RIGHT)==0)
	{	
		return D_RATE_RIGHT;}
	else if (a.compare(sD_U)==0)
	{	
		return D_U;}
	else if (a.compare(sD_DIFF_RATE)==0)
	{	
		return D_DIFF_RATE;
	}
	else 
	{
		cout << "INVALID INPUT" << endl;
		return -1;
	}

}




