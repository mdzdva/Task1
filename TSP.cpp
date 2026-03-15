#include "TSP.h"
#include <algorithm>
#include <iostream>
#include <cmath>

TSP::TSP(int n, const std::vector<Point>& pts)
    : N(n), cities(pts), distances(n, std::vector<double>(n, 0.0)) {
    
    std::random_device rd;
    rg.seed(rd());
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                distances[i][j] = distance(i, j);
            }
        }
    }
}

double TSP::distance(int i, int j) const {
    double dx = cities[i].x - cities[j].x;
    double dy = cities[i].y - cities[j].y;
    return std::sqrt(dx * dx + dy * dy);
}

std::vector<int> TSP::get_zero_solution() const {
    std::vector<int> solution(N);
    for(int i = 0; i < N; i++) {
        solution[i] = i;
    }
    
    for(int i = N - 1; i > 0; i--) {
        std::uniform_int_distribution<int> dist(0, i);
        int j = dist(rg);
        int temp = solution[i];
        solution[i] = solution[j];
        solution[j] = temp;
    }
    
    return solution;
}

bool TSP::is_correct_solution(const std::vector<int>& sol) const {
    if(sol.size() != static_cast<size_t>(N)) {
        return false;
    }
    
    std::vector<bool> visited(N, false);
    for(int i = 0; i < N; i++) {
        int city = sol[i];
        if(city < 0 || city >= N || visited[city]) {
            return false;
        }
        visited[city] = true;
    }
    
    return true;
}

int TSP::how_good_is_solution(const std::vector<int>& sol) const {
    return -static_cast<int>(total_distance(sol));
}

double TSP::total_distance(const std::vector<int>& sol) const {
    double dist = 0.0;
    for(int i = 0; i < N - 1; i++) {
        dist += distances[sol[i]][sol[i + 1]];
    }
    dist += distances[sol[N - 1]][sol[0]];
    return dist;
}

void TSP::print_solution(const std::vector<int>& sol) const {
    std::cout << static_cast<int>(total_distance(sol)) << '\n';
    for(int i = 0; i < N; i++) {
        if(i > 0) std::cout << ' ';
        std::cout << sol[i];
    }
    std::cout << '\n';
}

// 2-opt
std::vector<int> TSP::two_opt(const std::vector<int>& route, int i, int j) const {
    std::vector<int> new_route = route;
    int left = i + 1;
    int right = j;
    
    while(left < right) {
        int temp = new_route[left];
        new_route[left] = new_route[right];
        new_route[right] = temp;
        ++left;
        --right;
    }
    
    return new_route;
}

// 3-opt
std::vector<int> TSP::three_opt_case(const std::vector<int>& route, int i, int j, int k, int case_num) const {
    std::vector<int> new_route;
    new_route.reserve(N);
    
    if(case_num == 0) {
        for(int idx = 0; idx <= i; idx++) new_route.push_back(route[idx]);
        for(int idx = j; idx > i; idx--) new_route.push_back(route[idx]);
        for(int idx = j + 1; idx <= k; idx++) new_route.push_back(route[idx]);
        for(int idx = k + 1; idx < N; idx++) new_route.push_back(route[idx]);
    }
    else if(case_num == 1) {
        for(int idx = 0; idx <= i; idx++) new_route.push_back(route[idx]);
        for(int idx = i + 1; idx <= j; idx++) new_route.push_back(route[idx]);
        for(int idx = k; idx > j; idx--) new_route.push_back(route[idx]);
        for(int idx = k + 1; idx < N; idx++) new_route.push_back(route[idx]);
    }
    else if(case_num == 2) {
        for(int idx = 0; idx <= i; idx++) new_route.push_back(route[idx]);
        for(int idx = j; idx > i; idx--) new_route.push_back(route[idx]);
        for(int idx = k; idx > j; idx--) new_route.push_back(route[idx]);
        for(int idx = k + 1; idx < N; idx++) new_route.push_back(route[idx]);
    }
    else {
        for(int idx = 0; idx <= i; idx++) new_route.push_back(route[idx]);
        for(int idx = j + 1; idx <= k; idx++) new_route.push_back(route[idx]);
        for(int idx = i + 1; idx <= j; idx++) new_route.push_back(route[idx]);
        for(int idx = k + 1; idx < N; idx++) new_route.push_back(route[idx]);
    }
    
    return new_route;
}

std::vector<int> TSP::get_neigbour_solution(const std::vector<int>& current) const {
    std::uniform_int_distribution<int> opt_dist(0, 1);
    int opt_type = opt_dist(rg);
    
    if(opt_type == 0) {
        std::uniform_int_distribution<int> idx_dist(0, N - 1);
        int i = idx_dist(rg);
        int j = idx_dist(rg);
        
        if(i > j) {
            int temp = i;
            i = j;
            j = temp;
        }
        
        if(j - i < 2) {
            return current;
        }
        
        return two_opt(current, i, j);
    }
    else {
        std::uniform_int_distribution<int> idx_dist(0, N - 1);
        int i = idx_dist(rg);
        int j = idx_dist(rg);
        int k = idx_dist(rg);
        
        if(i > j) {
            int temp = i;
            i = j;
            j = temp;
        }
        if(j > k) {
            int temp = j;
            j = k;
            k = temp;
        }
        if(i > j) {
            int temp = i;
            i = j;
            j = temp;
        }
        
        if(k - j < 2 || j - i < 2) {
            return current;
        }
        
        std::uniform_int_distribution<int> case_dist(0, 3);
        int case_num = case_dist(rg);
        
        return three_opt_case(current, i, j, k, case_num);
    }
}
