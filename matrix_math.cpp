#include "matrix_math.h"

namespace {

inline size_t idx(int i, int j, int n) {
    return static_cast<size_t>(i) * static_cast<size_t>(n) + static_cast<size_t>(j);
}

}  // namespace

std::vector<int> naiveMatrixMultiplication(
    const std::vector<int>& a,
    const std::vector<int>& b,
    int n)
{
    std::vector<int> c(static_cast<size_t>(n) * static_cast<size_t>(n), 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[idx(i, j, n)] += a[idx(i, k, n)] * b[idx(k, j, n)];
            }
        }
    }

    return c;
}

std::vector<int> tiledMatrixMultiplication(
    const std::vector<int>& a,
    const std::vector<int>& b,
    int n,
    int tile)
{
    std::vector<int> c(static_cast<size_t>(n) * static_cast<size_t>(n), 0);

    for (int i = 0; i < n; i += tile) {
        for (int j = 0; j < n; j += tile) {
            for (int k = 0; k < n; k += tile) {
                for (int ii = i; ii < i + tile; ii++) {
                    for (int jj = j; jj < j + tile; jj++) {
                        for (int kk = k; kk < k + tile; kk++) {
                            c[idx(ii, jj, n)] +=
                                a[idx(ii, kk, n)] * b[idx(kk, jj, n)];
                        }
                    }
                }
            }
        }
    }

    return c;
}

double gflopsAchieved(float n, double ms) {
    return (2.0 * n * n * n) / (ms * 1e6);
}
