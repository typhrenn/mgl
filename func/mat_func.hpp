#pragma once

#include "../core/mat.hpp"
#include "../core/vec.hpp"

namespace mgl {
    template <int C, int R, typename T = float>
    constexpr inline vec<C, T> row(const mat<C, R, T> &m, int index) noexcept {
        vec<C, T> res;
        for (int i = 0; i < C; ++i) res[i] = m[i][index];
        return res;
    }

    // column
    template <int C, int R, typename T = float>
    constexpr inline vec<R, T> column(const mat<C, R, T> &m, int index) noexcept {
        return m[index];
    }

    // matrix transpose
    template <int C, int R, typename T = float>
    constexpr inline mat<R, C, T> transpose(const mat<C, R, T> &m) noexcept {
        mat<R, C, T> res;
        for (int c = 0; c < C; ++c) {
            for (int r = 0; r < R; ++r) {
                res[r][c] = m[c][r];
            }
        }
        return res;
    }

    // identity matrix
    template <int S, typename T = float>
    constexpr inline mat<S, S, T> identity() noexcept {
        mat<S, S, T> m(static_cast<T>(0));
        for (int i = 0; i < S; ++i) m[i][i] = static_cast<T>(1);
        return m;
    }

}
