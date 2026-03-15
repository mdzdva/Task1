#include "Knapsack.h"
#include "Solver.h"
#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int N, W;
    std::cin >> N >> W;
    
    std::vector<Item> items(N);
    for(int i = 0; i < N; i++) {
        std::cin >> items[i].value >> items[i].weight;
    }
    
    Knapsack knapsack(N, W, items);
    Solver solver(5000, 100);
    
    std::vector<int> solution = solver.solve(knapsack);
    knapsack.print(solution);
    
    return 0;
}
