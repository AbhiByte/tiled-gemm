#include <iostream>
#include <vector>
#include <chrono>   // Essential for timing
#include <iomanip>  // For better number formatting
#include "matrix_math.h"

int main() {
    int N = 512;
    int T = 32;

    std::vector<std::vector<int>> matA(N, std::vector<int>(N, 1));
    std::vector<std::vector<int>> matB(N, std::vector<int>(N, 2));

    // Start clock
    auto t0 = std::chrono::high_resolution_clock::now();
    // Call the function
    auto resultNaive = naiveMatrixMultiplication(matA, matB, N);
    auto t1 = std::chrono::high_resolution_clock::now();

    // tiled
    auto t2 = std::chrono::high_resolution_clock::now();
    auto resultTiled = tiledMatrixMultiplication(matA, matB, N, T);
    auto t3 = std::chrono::high_resolution_clock::now();


    // Calculate duration in milliseconds
    double msNaive = std::chrono::duration<double, std::milli>(t1 - t0).count();
    double gflopsNaive = gflopsAchieved(N, msNaive);
    double msTiled = std::chrono::duration<double, std::milli>(t3 - t2).count();
    double gflopsTiled = gflopsAchieved(N, msTiled);
    double speedup = msNaive / msTiled;

    // --- Fancy Table Output ---
    std::cout << "\nMatrix Multiplication Benchmark (N=" << N << ", Tile=" << T << ")\n";
    std::cout << std::string(50, '-') << "\n";
    std::cout << std::left << std::setw(15) << "Version" 
              << std::setw(15) << "Time (ms)" 
              << std::setw(15) << "GFLOPS" << "\n";
    std::cout << std::string(50, '-') << "\n";

    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(15) << "Naive" 
              << std::setw(15) << msNaive 
              << std::setw(15) << gflopsNaive << "\n";

    std::cout << std::left << std::setw(15) << "Tiled" 
              << std::setw(15) << msTiled 
              << std::setw(15) << gflopsTiled << "\n";
    
    std::cout << std::string(50, '-') << "\n";
    std::cout << "Total Speedup: " << speedup << "x" << std::endl;

    return 0;
}


        


