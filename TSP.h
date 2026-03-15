#ifndef TSP_H
#define TSP_H

#include "Task.h"
#include "Point.h"
#include <vector>
#include <random>

class TSP: public Task {
private:
    int N;
    std::vector<Point> cities;
    std::vector<std::vector<double>> distances;
    mutable std::mt19937 rg;
    
    double distance(int i, int j) const;
    std::vector<int> two_opt(const std::vector<int>& route, int i, int j) const;
    std::vector<int> three_opt_case(const std::vector<int>& route, int i, int j, int k, int case_num) const;
    
public:
    TSP(int n, const std::vector<Point>& pts);
    
    std::vector<int> get_zero_solution() const override;
    std::vector<int> get_neigbour_solution(const std::vector<int>& current) const override;
    int how_good_is_solution(const std::vector<int>& sol) const override;
    bool is_correct_solution(const std::vector<int>& sol) const override;
    
    double total_distance(const std::vector<int>& sol) const;
    void print_solution(const std::vector<int>& sol) const;
};

#endif
