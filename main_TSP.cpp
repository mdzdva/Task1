#include "TSP.h"
#include "Solver.h"
#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int N;
    std::cin >> N;
    
    std::vector<Point> cities(N);
    for(int i = 0; i < N; i++) {
        std::cin >> cities[i].x >> cities[i].y;
    }
    
    TSP tsp(N, cities);
    Solver solver(10000, 200);
    
    std::vector<int> solution = solver.solve(tsp);
    tsp.print_solution(solution);
    
    return 0;
}
