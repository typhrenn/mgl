#pragma once

#include "../quat.hpp"

namespace mgl {
	template <typename T>
	constexpr inline Quat<T> Quat<T>::operator*(const Quat<T> &q2) const noexcept {
		return Quat<T>{
			w * q2.x + x * q2.w + y * q2.z - z * q2.y,
			w * q2.y - x * q2.z + y * q2.w + z * q2.x,
			w * q2.z + x * q2.y - y * q2.x + z * q2.w,
			w * q2.w - x * q2.x - y * q2.y - z * q2.z
		};
	}

	template <typename T>
	constexpr inline Quat<T>::operator mat<4, 4, T>() const noexcept {
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
}