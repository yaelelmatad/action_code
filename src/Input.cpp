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

Input::Input()
{
}

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
				indicator = StringToInt(name_of_value);
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
				indicator = StringToInt(name_of_value);
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

void Input::ReadInput(char* in, int myRank)
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
				indicator = StringToInt(name_of_value);
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
				indicator = StringToInt(name_of_value);
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



int Input::GetIntInput(int indicator) const
{
	return intParams[indicator];
}

double Input::GetDoubleInput(int indicator) const
{
	return doubleParams[indicator];
}

// static
int Input::StringToInt(string a)
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
	MATCH_STRING_TO_ENUM( N_TRAJS_EQUIL )
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




