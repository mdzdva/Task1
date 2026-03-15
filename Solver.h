#ifndef SOLVER_H
#define SOLVER_H

#include "Task.h"
#include <vector>

class Solver {
private:
    int max_iterations;
    int max_neighbors;
    
public:
    Solver(int max_iter = 5000, int max_neigh = 100);
    std::vector<int> solve(const Task& problem) const;
};

#endif
