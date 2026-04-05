#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "matrix_math.h"

int main() {
    const int n = 512;
    const int tile = 32;

    std::vector<int> matA(static_cast<size_t>(n) * n, 1);
    std::vector<int> matB(static_cast<size_t>(n) * n, 2);

    auto t0 = std::chrono::high_resolution_clock::now();
    auto resultNaive = naiveMatrixMultiplication(matA, matB, n);
    auto t1 = std::chrono::high_resolution_clock::now();

    auto t2 = std::chrono::high_resolution_clock::now();
    auto resultTiled = tiledMatrixMultiplication(matA, matB, n, tile);
    auto t3 = std::chrono::high_resolution_clock::now();

    double msNaive = std::chrono::duration<double, std::milli>(t1 - t0).count();
    double gflopsNaive = gflopsAchieved(static_cast<float>(n), msNaive);
    double msTiled = std::chrono::duration<double, std::milli>(t3 - t2).count();
    double gflopsTiled = gflopsAchieved(static_cast<float>(n), msTiled);
    double speedup = msNaive / msTiled;

    std::cout << "\nMatrix Multiplication Benchmark (N=" << n << ", Tile=" << tile << ")\n";
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

    (void)resultNaive;
    (void)resultTiled;

    return 0;
}
