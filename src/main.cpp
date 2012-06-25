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

#include "trajectory.h"
#include "slice.h"
#include "config.h"
#include "dynamics.h"
#include "input.h"

int main (int argc, char * const argv[]) {
    // insert code here...
	//dynamics test2 (test, 1.0, 1.0, true, 1.0, 1.0);
	//trajectory test3(2.0, 1.0, 10, 3, 3);

	
	
	input runInput("inputFile");
	config test(runInput);
	trajectory trajectory(runInput);
	dynamics test2(runInput, test);	//config test3(test());
    return 0;


}

