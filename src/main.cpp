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

int main (int argc, char * const argv[]) {
    // insert code here...
	config test(0.5,5);
	//dynamics test2 (test, 1.0, 1.0, 1.0, 1.0);
	config test3(test());
    return 0;


}

