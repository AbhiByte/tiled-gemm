#include "matrix_math.h"

std::vector<std::vector<int>> naiveMatrixMultiplication(
    const std::vector<std::vector<int>>& a, 
    const std::vector<std::vector<int>>& b, 
    int N) 
{
    // Initialize a 2D vector of size N x N filled with zeros
    std::vector<std::vector<int>> c(N, std::vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return c;
}

std::vector<std::vector<int>> tiledMatrixMultiplication(
    const std::vector<std::vector<int>>& a, 
    const std::vector<std::vector<int>>& b, 
    int N, int T) 
{
    std::vector<std::vector<int>> c(N, std::vector<int>(N, 0));

    for (int i = 0; i < N; i += T) {
        for (int j = 0; j < N; j += T) {
            for (int k = 0; k < N; k += T) {
                for (int ii = i; ii < i+T; ii++){
                    for (int jj = j; jj < j+T; jj++){
                        for (int kk = k; kk < k+T; kk++){
                            c[ii][jj] += a[ii][kk] * b[kk][jj];
                        }
                    }
                }  
            }
        }
    }

    return c;
}

double gflopsAchieved(int N, double ms) {
    return (2.0 * N * N * N) / (ms * 1e6);
}