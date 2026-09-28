#pragma once

#include "../vec.hpp"
#include "../mat.hpp"

namespace mgl {

	// vector + vector
    template <int L, typename T>
    constexpr inline vec<L, T> operator+(vec<L, T> a, vec<L, T> b) noexcept {
        vec<L, T> result;
        for (int i = 0; i < L; ++i) {
            result[i] = a[i] + b[i];
        }
        return result;
    }

	// vector - vector
    template <int L, typename T>
    constexpr inline vec<L, T> operator-(vec<L, T> a, vec<L, T> b) noexcept {
        vec<L, T> result;
        for (int i = 0; i < L; ++i) {
            result[i] = a[i] - b[i];
        }
        return result;
    }

	// vector * vector
    template <int L, typename T>
    constexpr inline vec<L, T> operator*(vec<L, T> a, vec<L, T> b) noexcept {
        vec<L, T> result;
        for (int i = 0; i < L; ++i) {
            result[i] = a[i] * b[i];
        }
        return result;
    }

	// vector / vector
    template <int L, typename T>
    constexpr inline vec<L, T> operator/(vec<L, T> a, vec<L, T> b) noexcept {
        vec<L, T> result;
        for (int i = 0; i < L; ++i) {
            result[i] = a[i] / b[i];
        }
        return result;
    }

	// vector * scalar
    template <int L, typename T>
    constexpr inline vec<L, T> operator*(vec<L, T> v, T scalar) noexcept {
        vec<L, T> result;
        for (int i = 0; i < L; ++i) {
            result[i] = v[i] * scalar;
        }
        return result;
    }

	// scalar * vector
    template <int L, typename T>
    constexpr inline vec<L, T> operator*(T scalar, vec<L, T> v) noexcept {
        return v * scalar;
    }

	// vector / scalar
    template <int L, typename T>
    constexpr inline vec<L, T> operator/(vec<L, T> v, T scalar) noexcept {
        vec<L, T> result;
        for (int i = 0; i < L; ++i) {
            result[i] = v[i] / scalar;
        }
        return result;
    }

	// vector += vector
    template <int L, typename T>
    constexpr inline vec<L, T>& operator+=(vec<L, T> &a, const vec<L, T> &b) noexcept {
        for (int i = 0; i < L; ++i) {
            a[i] += b[i];
        }
        return a;
    }

	// vector -= vector
    template <int L, typename T>
    constexpr inline vec<L, T>& operator-=(vec<L, T> &a, const vec<L, T> &b) noexcept {
        for (int i = 0; i < L; ++i) {
            a[i] -= b[i];
        }
        return a;
    }

	// vector *= vector
    template <int L, typename T>
    constexpr inline vec<L, T>& operator*=(vec<L, T> &a, const vec<L, T> &b) noexcept {
        for (int i = 0; i < L; ++i) {
            a[i] *= b[i];
        }
        return a;
    }

	// vector /= vector
    template <int L, typename T>
    constexpr inline vec<L, T>& operator/=(vec<L, T> &a, const vec<L, T> &b) noexcept {
        for (int i = 0; i < L; ++i) {
            a[i] /= b[i];
        }
        return a;
    }

	// vector *= scalar
    template <int L, typename T>
    constexpr inline vec<L, T>& operator*=(vec<L, T> &v, T scalar) noexcept {
        for (int i = 0; i < L; ++i) {
            v[i] *= scalar;
        }
        return v;
    }

	// vector /= scalar
    template <int L, typename T>
    constexpr inline vec<L, T>& operator/=(vec<L, T> &v, T scalar) noexcept {
        for (int i = 0; i < L; ++i) {
            v[i] /= scalar;
        }
        return v;
    }

    // matrix * vector
    template <int C, int R, typename T>
    constexpr inline vec<C, T> operator*(const mat<C, R, T> &m, const vec<C, T> &v) noexcept {
        vec<C, T> res;
        for (int i = 0; i < C; i++) {
            res = res + m[i] * v[i];
        }

        return res;
    }

}
