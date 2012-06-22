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
	config test(0.5,20);
	dynamics test2 (test, 1.0, 1.0, true, 1.0, 1.0);
	//dynamics test2(a config, T, U, if hard = true, rate left, rate right)
	//config test3(test());
    return 0;


}

