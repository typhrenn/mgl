#pragma once

#include "../mat.hpp"

namespace mgl {

    // matrix * matrix
    template <int C1, int R1, int C2, typename T>
    constexpr inline mat<C2, R1, T> operator*(const mat<C1, R1, T> &a, const mat<C2, C1, T> &b) noexcept {
        mat<C2, R1, T> result;
        for (int j = 0; j < C2; ++j) {
            vec<R1, T> col{};
            for (int k = 0; k < C1; ++k) {
                col = col + a[k] * b[j][k];
            }
            result[j] = col;
        }
        return result;
    }

    // matrix + matrix
    template <int C, int R, typename T>
    constexpr inline mat<C, R, T> operator+(const mat<C, R, T> &a, const mat<C, R, T> &b) noexcept {
        mat<C, R, T> result;
        for (int i = 0; i < C; ++i) {
            result[i] = a[i] + b[i];
        }
        return result;
    }

    // matrix - matrix
    template <int C, int R, typename T>
    constexpr inline mat<C, R, T> operator-(const mat<C, R, T> &a, const mat<C, R, T> &b) noexcept {
        mat<C, R, T> result;
        for (int i = 0; i < C; ++i) {
            result[i] = a[i] - b[i];
        }
        return result;
    }

    // matrix * scalar
    template <int C, int R, typename T>
    constexpr inline mat<C, R, T> operator*(const mat<C, R, T> &m, T scalar) noexcept {
        mat<C, R, T> result;
        for (int i = 0; i < C; ++i) {
            result[i] = m[i] * scalar;
        }
        return result;
    }

    // scalar * matrix
    template <int C, int R, typename T>
    constexpr inline mat<C, R, T> operator*(T scalar, const mat<C, R, T> &m) noexcept {
        return m * scalar;
    }

    // matrix / scalar
    template <int C, int R, typename T>
    constexpr inline mat<C, R, T> operator/(const mat<C, R, T> &m, T scalar) noexcept {
        mat<C, R, T> result;
        for (int i = 0; i < C; ++i) {
            result[i] = m[i] / scalar;
        }
        return result;
    }

    // matrix += matrix
    template <int C, int R, typename T>
    constexpr inline mat<C, R, T>& operator+=(mat<C, R, T> &a, const mat<C, R, T> &b) noexcept {
        for (int i = 0; i < C; ++i) {
            a[i] += b[i];
        }
        return a;
    }

    // matrix -= matrix
    template <int C, int R, typename T>
    constexpr inline mat<C, R, T>& operator-=(mat<C, R, T> &a, const mat<C, R, T> &b) noexcept {
        for (int i = 0; i < C; ++i) {
            a[i] -= b[i];
        }
        return a;
    }

    // matrix *= scalar
    template <int C, int R, typename T>
    constexpr inline mat<C, R, T>& operator*=(mat<C, R, T> &m, T scalar) noexcept {
        for (int i = 0; i < C; ++i) {
            m[i] *= scalar;
        }
        return m;
    }

    // matrix /= scalar
    template <int C, int R, typename T>
    constexpr inline mat<C, R, T>& operator/=(mat<C, R, T> &m, T scalar) noexcept {
        for (int i = 0; i < C; ++i) {
            m[i] /= scalar;
        }
        return m;
    }

}
