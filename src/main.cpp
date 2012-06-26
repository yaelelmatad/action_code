#include <iostream>
#include <stdlib.h>
#include<math.h>
#include<time.h>
#include<stdio.h>
#include<float.h>
#include<iostream>
#include<fstream>
using namespace std;
float pi = 3.14159265;

#include "Trajectory.h"
#include "Slice.h"
#include "Config.h"
#include "Dynamics.h"
#include "Input.h"

int main (int argc, char * const argv[]) {
    // insert code here...
	//dynamics test2 (test, 1.0, 1.0, true, 1.0, 1.0);
	//trajectory test3(2.0, 1.0, 10, 3, 3);

	
	
	Input runInput("inputFile");
	Config test(runInput);
	//Trajectory trajectory(runInput);
	Slice testSlice(runInput, test, true);
	Dynamics test2(runInput);	//Config test3(test());
    return 0;


}

