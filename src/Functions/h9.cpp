#include "../rng.h"
#include "../problem.h"
#include "../utils.h"
#include "rastrigin.h"
#include "extendedF10.h"
#include "h9.h"

#include <assert.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

Hybrid9::Hybrid9(Configuration* config, int variantID):Problem(config, variantID){
	optimum = 0.0;
	problem1 = new ExtendedF10(config, BASIC);
	problem2 = new Rastrigin(config, SHIFTED);
}

Hybrid9::~Hybrid9(){
	delete problem1;
	delete problem2;
}

long double Hybrid9::evaluate(int dim, const double* x) {
	long double result = 0.0;

	switch(vID){
	case BASIC:
		result = h9Function(dim, x);
		break;
	default: cout<<"There is no function such that !!"<< endl;
	exit(0);
	break;
	} 

	return result;

}

long double Hybrid9::h9Function(int dim, const double* x){
	double part1[dim], part2[dim];
	int size1, size2;
	long double f1, f2;
	divideFunctions(x, part1, part2, 0.75, &size1, &size2);

	f1 = problem1->evaluate(size1,part1);
	f2 = problem2->evaluate(size2,part2);

	return f1+f2;
}
