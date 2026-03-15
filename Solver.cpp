#include "Solver.h"

Solver::Solver(int max_iter, int max_neigh)
    : max_iterations(max_iter), max_neighbors(max_neigh) {}

std::vector<int> Solver::solve(const Task& problem) const {
    std::vector<int> best_solution = problem.get_zero_solution();
    int best_objective = problem.how_good_is_solution(best_solution);
    
    bool improved = true;
    int iteration = 0;
    
    while(improved && iteration < max_iterations) {
        improved = false;
        
        int i = 0;
        while(i < max_neighbors && !improved) {
            std::vector<int> neighbour = problem.get_neigbour_solution(best_solution);
            
            if(problem.is_correct_solution(neighbour)) {
                int neighbour_objective = problem.how_good_is_solution(neighbour);
                
                if(neighbour_objective > best_objective) {
                    best_solution = neighbour;
                    best_objective = neighbour_objective;
                    improved = true;
                }
            }
            
            i++;
        }
        
        iteration++;
    }
    
    return best_solution;
}
