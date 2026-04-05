#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

// Keep assert() active in Release for this translation unit (CMake sets NDEBUG).
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>

#include "matrix_math.h"

namespace {

int maxAbsDiff(const std::vector<int>& cNaive,
               const std::vector<int>& cTiled,
               int n) {
    int diff = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            const int idx = i * n + j;
            diff = std::max(diff, std::abs(cNaive[idx] - cTiled[idx]));
        }
    }
    return diff;
}

}  // namespace

int main() {
    // Small N; tile divides n so the tiled kernel stays in-bounds.
    constexpr int n = 32;
    constexpr int tile = 8;

    std::vector<int> a(static_cast<size_t>(n) * n);
    std::vector<int> b(static_cast<size_t>(n) * n);
    for (int i = 0; i < n * n; ++i) {
        a[static_cast<size_t>(i)] = (i % 7) - 3;
        b[static_cast<size_t>(i)] = (i % 5) - 2;
    }

    const std::vector<int> cNaive = naiveMatrixMultiplication(a, b, n);
    const std::vector<int> cTiled = tiledMatrixMultiplication(a, b, n, tile);

    const int diff = maxAbsDiff(cNaive, cTiled, n);
    // Integer GEMM must match exactly. For float GEMM: assert(diff < 1e-3f);
    if (diff != 0) {
        std::cerr << "GEMM mismatch: max abs diff = " << diff << '\n';
    }
    assert(diff == 0);
    return 0;
}
