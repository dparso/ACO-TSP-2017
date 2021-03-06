#ifndef ACO_H
#define ACO_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

// parameters to set
const int ALGTYPE = 1; // 0 for EAS, 1 for ACS
const int NUM_ANTS = 20; // number of ants
const int ITERATIONS = 300; // number of iterations (200-300 should do it)
const double PHERO_INITAL = 1.0; // initial pheromone level for each leg
const double OPTIMAL_DEVIATION = 0.01; // percentage from the optimal
                                        //within which our solution will stop iterating
const double ALPHA = 1; // pheromone influence
const double BETA = 5.0; // heuristic influence
const double RHO = 0.01; // evaporation (0 < RHO < 1)

// this one only for EAS
const int ELITISM_FACTOR = NUM_ANTS;

// these three only for ACS (tau is the third and is defined in the class)
const double EPSILON = 0.1;
const double Q0 = 0.9;

/*   terminating mode:
 *      if TERM = 1, iteration will stop after ITERATIONS iterations.
 *      if TERM = 2, iteration will stop after our solution gets within
            OPTIMAL_DEVIATION percent of the optimal solution
 *      if TERM = 3, iteration will stop after either of the above
            options are satisfied
 */
const double TERM = 1;
// END PARAMETERS

typedef struct _point2d {
    double x, y;
} point2D;

typedef struct _city {
    point2D p;
    int ID;
} City;

typedef struct _leg {
    City city1, city2;
    double phero;
    double length;
    bool inBSF;
} Leg;

void printPoint(point2D p);
void printCity(City c);

typedef struct _ant {
    City city;
    vector<City> unvisited;
    vector<City> tour;
} Ant;

class ACOSolver {
public:
    ACOSolver(string fileName);
    //special constructor for testing
    ACOSolver(string fileName, double q0, double epsilon, double alpha, double beta, double rho);
    ~ACOSolver();

    vector<Ant> ants;
    vector<City> cities;
    vector<vector<Leg> > legs;
    vector<int> bsfRoute;
    double bsfRouteLength;

    int numAnts;
    string fileName;
    double q_0;
    double epsilon;
    double alpha;
    double beta;
    double rho;
    int optimal;

    double tau_0; //length of nearest neighbor tour, set by setTau()

    /* solver functions */
    vector<double> solve();
    bool terminated(int iterations);

    // helper functions
    bool inBSF(City city1, City city2);
    bool inTour(Ant a, Leg l);
    double calculateDistance(point2D City1, point2D City2);
    int getRandomCity(vector<City> unvisited);
    double getLegPhero(City city1, City city2);
    Leg getLeg(City cityA, City cityB);
    bool legMatchesCities(Leg theLeg, City cityA, City cityB);
    double calculateTourDistance(Ant a);
    void updateBSF();

private:
    void initAllLegs();
    void initAnts();
    void resetAnts();
    void readFile();
    int getGreedyNextCity(Ant k);
    void ACSGlobalPheroUpdate();
    void ACSLocalPheroUpdate(City cityA, City cityB);
    void EASPheroUpdate();
    void buildTours();
    void setTau();
    int getNextCity(Ant a);
};



#endif
