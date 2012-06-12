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
    std::cout << "Hello, World! BY Yael! on bubbly BUT NOW ON TPATH LAPTOPß\n";
	config test(0.5,2);
	dynamics test2 (test, 1.0, 1.0, 1.0, 1.0);
    return 0;


}

