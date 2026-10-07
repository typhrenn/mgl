#pragma once

#include <iostream>
#include <random>

#include "../mgl.hpp"

namespace Random {
	namespace detail {
		inline std::mt19937& engine() {
			thread_local std::mt19937 e{std::random_device{}()};
			return e;
		}
	}

	inline int Int(int min, int max) {
		std::uniform_int_distribution<int> dist(min, max);
		return dist(detail::engine());
	}

	inline float Float(float min, float max) {
		std::uniform_real_distribution<float> dist(min, max);
		return dist(detail::engine());
	}

	inline double Double(double min, double max) {
		std::uniform_real_distribution<double> dist(min, max);
		return dist(detail::engine());
	}

	template <int L, typename T = float>
	inline mgl::vec<L, T> Vector(T min, T max) {
		mgl::vec<L, T> v;
		std::uniform_real_distribution<T> dist(min, max);

		for (int i = 0; i < L; i++) {
			v[i] = dist(detail::engine());
		}

		return v;
	}

	template <typename T = float>
	inline mgl::quat<T> Quaternion() {
		std::uniform_real_distribution<T> dist(0.0, 1.0);
		
		T u1 = dist(detail::engine());

		T sqrt1_u1 = std::sqrt(1.0 - u1);
		T sqrt_u1  = std::sqrt(u1);

		T a = mgl::two_pi<T>() * dist(detail::engine());
		T b = mgl::two_pi<T>() * dist(detail::engine());

		return mgl::quat<T>{
			sqrt1_u1 * std::sin(a),
			sqrt1_u1 * std::cos(a),
			sqrt_u1  * std::sin(b),
			sqrt_u1  * std::cos(b)
		};
	}
}