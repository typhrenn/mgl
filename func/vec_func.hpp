#pragma once

#include <cmath>
#include "../core/vec.hpp"

namespace mgl {
    constexpr inline vec3 x_axis() noexcept {return vec3{1.0f, 0.0f, 0.0f};}
    constexpr inline vec3 y_axis() noexcept {return vec3{0.0f, 1.0f, 0.0f};}
    constexpr inline vec3 z_axis() noexcept {return vec3{0.0f, 0.0f, 1.0f};}

    template <int L, typename T = float>
    constexpr inline T dot(const vec<L, T> &a, const vec<L, T> &b) noexcept {
        T res = static_cast<T>(0);
        for (int i = 0; i < L; ++i) res += a[i] * b[i];
        return res;
    }

    // magnitude squared
    template <int L, typename T = float>
    constexpr inline T magnitude_squared(const vec<L, T> &v) noexcept {
        return dot(v, v);
    }

    // magnitude
    template <int L, typename T = float>
    inline T magnitude(const vec<L, T> &v) noexcept {
        return std::sqrt(magnitude_squared(v));
    }

    // normalize
    template <int L, typename T = float>
    inline vec<L, T> normalize(const vec<L, T> &v) noexcept {
        T inv_mag = static_cast<T>(1) / magnitude(v);
        vec<L, T> res;
        for (int i = 0; i < L; ++i) res[i] = v[i] * inv_mag;
        return res;
    }

    // vector reversal
    template <int L, typename T = float>
    constexpr inline vec<L, T> reverse(const vec<L, T> &v) noexcept {
        vec<L, T> res;
        for (int i = 0; i < L; ++i) res[i] = v[L - 1 - i];
        return res;
    }

	// vector inversion
	template <int L, typename T = float>
	constexpr inline vec<L, T> invert(const vec<L, T> &v) noexcept {
		vec<L, T> res;
		for (int i = 0; i < L; ++i) {
			res[i] = -v[i];
		}
		return res;
	}

    // vector reflection
    template <int L, typename T = float>
    constexpr inline vec<L, T> reflection(const vec<L, T> &incident, const vec<L, T> &normal) noexcept {
        T double_dot = static_cast<T>(2) * dot(incident, normal);
        vec<L, T> res;
        for (int i = 0; i < L; ++i) res[i] = incident[i] - double_dot * normal[i];
        return res;
    }

	// i prefered for the function to have it's own name despite doing the same thing as magnitude formula for clarity when writing code
	template <int L, typename T = float>
	inline T distance(const vec<L, T> &a, const vec<L, T> &b) noexcept {
		return magnitude(a - b); 
	}

    template <typename T = float>
    constexpr inline vec<3, T> transform_point(const mat<4, 4, T> &m, const vec<3, T> &v) noexcept {
        vec4 res = m * vec4{v.x, v.y, v.z, 1.0f};

        return vec3{res.x, res.y, res.z};
    }

    template <typename T = float>
    constexpr inline vec<3, T> cross(const vec<3, T> &a, const vec<3, T> &b) noexcept {
        return vec<3, T>{
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }

	template <typename T = float>
	constexpr inline vec<3, T> lerp(const vec<3, T> &a, const vec<3, T> &b, T t) {
		return a + (b - a) * t;
	}

	template <int L, typename T = float>
	constexpr inline vec<L, T> min(const vec<L, T> &a, const vec<L, T> &b) {
		vec<L, T> v;
		for (int i = 0; i < L; i++) {
			v[i] = std::min(a[i], b[i]);
		}

		return v;
	}

	template <int L, typename T = float>
	constexpr inline vec<L, T> max(const vec<L, T> &a, const vec<L, T> &b) {
		vec<L, T> res;
		for (int i = 0; i < L; i++) {
			res[i] = std::max(a[i], b[i]);
		}

		return res;
	}

	template <int L, typename T = float>
	constexpr inline vec<L, T> clamp(const vec<L, T> &v, const vec<L, T> &low, const vec<L, T> &high) {
		vec<L, T> res;
		for (int i = 0; i < L; i++) {
			if 		(v[i] < low[i]) 	res[i] = low[i];
			else if (v[i] > high[i]) 	res[i] = high[i];
			else 						res[i] = v[i];
		}

		return res;
	}

	template <typename T>
    constexpr inline T clamp(const T v, const T low, const T high) noexcept {
        if (v < low)  return low;
        if (v > high) return high;
        return v;
    }

	template <int L, typename T = float>
	constexpr inline vec<L, T> abs(const vec<L, T> &v) {
		vec<L, T> res;
		for (int i = 0; i < L; i++) {
			res[i] = std::abs(v[i]);
		}

		return res;
	}

	template <int L, typename T = float>
	constexpr inline vec<L, T> nlerp(const vec<L, T> &a, const vec<L, T> &b, T t) noexcept {
		return normalize(lerp(a, b, t));
	}
}
