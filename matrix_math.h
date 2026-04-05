#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include <vector>

// Just the signature/prototype
std::vector<std::vector<int>> naiveMatrixMultiplication(
    const std::vector<std::vector<int>>& a, 
    const std::vector<std::vector<int>>& b, 
    int N);


double gflopsAchieved(int N, double ms);

#endif