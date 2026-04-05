#include <iostream>
#include <vector>
#include <chrono>   // Essential for timing
#include <iomanip>  // For better number formatting
#include "matrix_math.h"

int main() {
    int N = 512;

    std::vector<std::vector<int>> matA(N, std::vector<int>(N, 1));
    std::vector<std::vector<int>> matB(N, std::vector<int>(N, 2));

    // Start clock
    auto t0 = std::chrono::high_resolution_clock::now();

    // Call the function
    auto result = naiveMatrixMultiplication(matA, matB, N);

    auto t1 = std::chrono::high_resolution_clock::now();

    // Calculate duration in milliseconds
    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    double gflops = gflopsAchieved(N, ms);

    std::cout << "Matrix Size: " << N << "x" << N << std::endl;
    std::cout << "Execution Time: " << std::fixed << std::setprecision(2) << ms << " ms" << std::endl;
    std::cout << "GFLOPS Achieved: " <<  std::fixed << std::setprecision(2) << gflops << std::endl;

    return 0;
}


        


