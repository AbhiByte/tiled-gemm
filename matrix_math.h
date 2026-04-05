#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include <vector>

// Row-major layout: element (i, j) is at index i * n + j.

std::vector<int> naiveMatrixMultiplication(
    const std::vector<int>& a,
    const std::vector<int>& b,
    int n);

std::vector<int> tiledMatrixMultiplication(
    const std::vector<int>& a,
    const std::vector<int>& b,
    int n,
    int tile);

double gflopsAchieved(float n, double ms);

#endif
