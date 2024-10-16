#include "../rng.h"
#include "../problem.h"
#include "../utils.h"
#include "rosenbrock.h"
#include "extendedF10.h"
#include "h8.h"

#include <assert.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

Hybrid8::Hybrid8(Configuration* config, int variantID):Problem(config, variantID){
	optimum = 0.0;
	problem1 = new ExtendedF10(config, BASIC);
	problem2 = new Rosenbrock(config, SHIFTED);
}

Hybrid8::~Hybrid8(){
	delete problem1;
	delete problem2;
}

long double Hybrid8::evaluate(int dim, const double* x) {
	long double result = 0.0;

	switch(vID){
	case BASIC:
		result = h8Function(dim, x);
		break;
	default: cout<<"There is no function such that !!"<< endl;
	exit(0);
	break;
	} 

	return result;

}



long double Hybrid8::h8Function(int dim, const double* x){
	double part1[dim], part2[dim];
	int size1, size2;
	long double f1, f2;
	divideFunctions(x, part1, part2, 0.75, &size1, &size2);

	f1 = problem1->evaluate(size1,part1);
	f2 = problem2->evaluate(size2,part2);

	return f1+f2;
}
