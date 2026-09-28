#pragma once

#include <array>
#include "mat.hpp"

namespace mgl {

	// quaternion
	template <typename T = float>
	struct alignas(4 * sizeof(T)) quat {
		union {
			struct { T x, y, z, w; };
			std::array<T, 4> data;
		};

		constexpr quat() noexcept : x(0), y(0), z(0), w(1) {}
		constexpr quat(T _x, T _y, T _z, T _w) noexcept : x(_x), y(_y), z(_z), w(_w) {}

		constexpr T& operator[](int index) noexcept { return data[index]; }
		constexpr const T& operator[](int index) const noexcept { return data[index]; }

		explicit operator mat<4, 4, T>() const noexcept {
			mat<4, 4, T> res;

			T xx = x * x;
			T yy = y * y;
			T zz = z * z;

			T xy = x * y;
			T xz = x * z;
			T yz = y * z;

			T wx = w * x;
			T wy = w * y;
			T wz = w * z;

			res.columns[0][0] = static_cast<T>(1) - (static_cast<T>(2) * yy) - (static_cast<T>(2) * zz);
			res.columns[1][0] = (static_cast<T>(2) * xy) - (static_cast<T>(2) * wz);
			res.columns[2][0] = (static_cast<T>(2) * xz) + (static_cast<T>(2) * wy);
			res.columns[3][0] = static_cast<T>(0);

			res.columns[0][1] = (static_cast<T>(2) * xy) + (static_cast<T>(2) * wz);
			res.columns[1][1] = static_cast<T>(1) - (static_cast<T>(2) * xx) - (static_cast<T>(2) * zz);
			res.columns[2][1] = (static_cast<T>(2) * yz) - (static_cast<T>(2) * wx);
			res.columns[3][1] = static_cast<T>(0);

			res.columns[0][2] = (static_cast<T>(2) * xz) - (static_cast<T>(2) * wy);
			res.columns[1][2] = (static_cast<T>(2) * yz) + (static_cast<T>(2) * wx);
			res.columns[2][2] = static_cast<T>(1) - (static_cast<T>(2) * xx) - (static_cast<T>(2) * yy);
			res.columns[3][2] = static_cast<T>(0);

			res.columns[0][3] = static_cast<T>(0);
			res.columns[1][3] = static_cast<T>(0);
			res.columns[2][3] = static_cast<T>(0);
			res.columns[3][3] = static_cast<T>(1);

			return res;
		}
	};

	using quat_f = quat<float>;

	template<typename T = float>
	constexpr inline mat<4, 4, T> quat_to_mat4x4(const quat<T> &q) noexcept {
		return static_cast<mat<4, 4, T>>(q);
	}

	constexpr inline quat_f identity_quat = quat_f{0.0f, 0.0f, 0.0f, 1.0f};

}

#include "detail/quat_operators.inl"
