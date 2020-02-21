/*
 * swarm.h
 *
 *  Created on: Jun 20, 2018
 *      Author: leonardo
 */

#ifndef SWARM_H_
#define SWARM_H_

#include <vector>
#include "problem.h"
#include "config.h"
#include "particle.h"
#include "utils.h"

#include <math.h>

/* Simplified swarm structure */
struct ssArray {
	long double* eval;   /* value of the solution */
	int* id;  		     /* particle id */
};

class Swarm {

protected:

	Problem* problem;				/* the optimization problem */
	vector<Particle*> swarm;		/* the swarm */
	long int size;					/* number of particles*/

	struct Solution global_best;    /* best solution in the swarm*/
	Particle *best_particle;        /* best particle */
	bool init;
	bool ranked;					/* implement particle rankings */
	bool hierarchical;				/* hierarchical topology flag */

public:

	Swarm ();
	~Swarm();
	Swarm (Problem* problem, Configuration* config); /*Create swarm structure*/
	//Swarm (const Swarm &s, Configuration* config);

	//Swarm& operator= (const Swarm& s);

	void updateGlobalBest(double* new_x, double eval);
	void moveSwarm(Configuration* config, long int iteration, const double minBound, const double maxBound);
	int getInformants(Configuration* config, int particleID, long int iteration);	//returns the number of informants of a particle

	// Inertia and acceleration coefficients
	void computeAccelerationCoefficients(Configuration* config, long int iteration);
	void decomposePhi2(int modelOfInflu, int part_id, int numInformants);
	double computeOmega1(Configuration* config, long int iteration, long int id, bool newIteration);
	double computeOmega2(Configuration* config);
	double computeOmega3(Configuration* config);
	double computeAvgVelocity(Configuration* config);
	//void rankParticles(SimplifySwarm* particles);

	// GlobalBest particle
	Solution getGlobalBest();
	void printGbest(unsigned int dimensions);

	/* Available topologies*/
	void createFullyConnectedTopology();
	void createRingTopology();
	void createWheelTopology();
	void createRandomEdge();
	void createVonNeumannTopology();
	void updateTimeVaryingTopology(Configuration* config, long int iterations);

	//Hierarchical topology
	void createHierarchical(int branching, int finalPopSize);
	void printTree(int branching, long swarm_size);
	void swapNodes(int newParent, int newH, int newWidth, int parentNode, int parentH, int parentWidth, int branching, int h, int width, int iterCount);
	void updateTree(int branching);
	bool isHierarchical();
	void getParticleParentsIDs(int particleID, int *ParentsArray1D);
	void printAllParentNodes();
	int getParticleNumParents(int particleID);

	//Perturbation
	void updatePerturbationVariables(Configuration* config, double previousGbest_eval, double currentGbest_eval, long int iteration);
	double computeAngleOfRRM(Configuration* config, long int iteration);

	//Population size
	void resizeSwarm(Problem* problem, Configuration* config, long int iteration);
	void addParticles(Problem* problem, Configuration* config, int numOfParticles, long int iteration);
	void updateTopologyConnections(Configuration* config, long previous_size, long int iteration);
	void addParticlesInLastLevel(int first, int last, int branching);
	void updateHierarchical(int branching, long previous_size);
	//void clearResizeSimpSwarm(vector<SimplifySwarm> &sSwarm);
	void clearResizeSimpSwarm(Configuration* config, long int iteration);

	//Utils
	void rankParticles(vector<SimplifySwarm> &sSwarm);
	void mergeSort(ssArray* arr, int l, int r);
	void merge(ssArray* arr, int l, int m, int r);


};

#endif /* SWARM_H_ */
