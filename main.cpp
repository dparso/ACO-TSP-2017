#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include "ACO.h"

using namespace std;

void printMedian(vector<vector<double> > trials, int num);

void printInfo() {
    cout << endl;
    cout << "Usage:\nFor all Ant Colony Optimization:\n./main filename" << endl;
    cout << "filename = path to the tsp file to use" << endl;
    cout << "Sample input: './main ALL_tsp/berlin52.tsp'" << endl;
    cout << endl;
}

string files[4] = {"d2103","pcb3038","fnl4461","rl5915"};
double alphas[5] = {0.5,1.0,1.2,1.4,1.6};
double betas[5] = {1,2,3,4,5};
double rhos[5] = {0.01, 0.1, 0.25, 0.5, 0.75};
double epsilons[5] = {0.01, 0.1, 0.25, 0.5, 0.75};
double qs[5] = {0.25, 0.5, 0.75, 0.9, 1};
const static double TRIALS = 4;

bool compare(vector<double > i, vector<double> j) {
    return (i[i.size() - 2], j[j.size() - 2]);
}

void test() {
    int num = 0;
    // for(int q = 0; q < 5; q++) {
        // for(int eps = 3; eps < 5; eps++) {
            // for(int f = 0; f < 4; f++) {
                // for(int a = 0; a < 5; a++) {
                    // for(int b = 0; b < 5; b++) {
                        // for(int r = 0; r < 5; r++) {
                        int f = 2;
                        int a = 0;
                        int b = 3;
                        int r = 1;
                        int q = 3;
                        int eps = 0;
                            vector<vector<double> > trials;
                            for(int i = 0; i < TRIALS; i++) {
                                string fileName = "ALL_tsp/" + files[f] + ".tsp";
                                ACOSolver solver(fileName, qs[q], epsilons[eps], alphas[a], betas[b], rhos[r]);

                                trials.push_back(solver.solve());
                            }
                            sort(trials.begin(), trials.end(), compare);
                            cout << "% ACS **INPUTS** file: " << files[f] << ", alpha: " << alphas[a];
                            cout << ", beta: " << betas[b] << ", rho: " << rhos[r] << ", epsilon: " << epsilons[eps] << ", q_0: " << qs[q];
                            cout << "; median best over " << TRIALS << " trials." << endl;
                            cout << "% The best from file is: ";
                            cout << trials[0][trials[0].size() - 1] << endl;
                            printMedian(trials, num);
                            num++;
                        // }
                    // }
                // }
            // }
        // }
    // }
}

void printMedian(vector<vector<double> > trials, int num) {
    int med = trials.size()/2;

    cout << "\\begin{filecontents*}{data" << num << ".txt}" << endl;
    //only go to size() - 1 (i.e. exclude the last one) because the last one is the optimal
    for(int i = 0; i < trials[med].size() - 1; i++) {
        cout << "\t" << i << "  " << trials[med][i] << endl;
    }
    cout << "\\end{filecontents*}" << endl;
    cout << endl << endl;
}

int main (int argc, char** argv) {
    if(argc != 2) {
        // incorrect input
        printInfo();
        exit(1);
    } else {
        string fileName = argv[1];
        cout << fileName << endl;

        ACOSolver solver(fileName);

        solver.solve();

        // test();
    }

}
