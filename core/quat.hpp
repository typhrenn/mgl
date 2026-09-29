#pragma once

#include <array>
#include "mat.hpp"
#include "types.hpp"
#include "vec.hpp"

namespace mgl {

	// quaternion
	template <typename T = float>
	class alignas(4 * sizeof(T)) Quat {
		public:
			union {
				struct { T x, y, z, w; };
				std::array<T, 4> data;
			};

			constexpr Quat() noexcept : x(0), y(0), z(0), w(1) {}
			constexpr Quat(T _x, T _y, T _z, T _w) noexcept : x(_x), y(_y), z(_z), w(_w) {}

			constexpr T& operator[](int index) noexcept { return data[index]; }
			constexpr const T& operator[](int index) const noexcept { return data[index]; }

			// operators
			explicit operator mat<4, 4, T>() const noexcept;
			constexpr inline Quat<T> operator*(const Quat<T> &q2) const noexcept;

			constexpr inline mat<4, 4, T> matrix() noexcept {
				return static_cast<mat<4, 4, T>>(*this);
			}

			static inline Quat<T> single_axis_quat(const vec<3, T> &axis, radian<T> rad) noexcept;
			static inline Quat<T> full_axis_quat(const vec<3, T> &rot) noexcept;

			constexpr inline T dot(const Quat<T> &b) const noexcept;
			inline Quat<T>& normalize() noexcept;
			constexpr inline Quat<T>& conjugate() noexcept;
			constexpr inline Quat<T>& inverse() noexcept;
			inline Quat<T>& slerp(const Quat<T> &b, T t) noexcept;
			constexpr inline vec3 rotate(const vec3 &v) const noexcept;
			inline vec<3, radian<>> quat_to_euler() const noexcept;
	};

	using Quatf = Quat<float>;

	constexpr inline Quatf identity_quat = Quatf{0.0f, 0.0f, 0.0f, 1.0f};

}

#include "detail/quat_operators.inl"