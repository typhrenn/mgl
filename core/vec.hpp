#pragma once

#include <array>
#include <ostream>

namespace mgl {

    template <int L, typename T> struct vec;

    template <typename T> struct vec<2, T> {
        union {
            struct { T x, y; };
            std::array<T, 2> data;
        };

        constexpr vec() noexcept : x(0), y(0) {}
        constexpr vec(T _x, T _y) noexcept : x(_x), y(_y) {}

        constexpr T& operator[](int index) noexcept {return data[index];}
        constexpr const T& operator[](int index) const noexcept {return data[index];}

		friend std::ostream& operator<<(std::ostream& os, const vec<2, T> v) {
			os << "{x='" << v.x << "',y='" << v.y << "'}";
			return os;
		}
    };

    template <typename T> struct vec<3, T> {
        union {
            struct { T x, y, z; };
            std::array<T, 3> data;
        };

        constexpr vec() noexcept : x(0), y(0), z(0) {}
        constexpr vec(T _x, T _y, T _z) noexcept : x(_x), y(_y), z(_z) {}

        constexpr T& operator[](int index) noexcept {return data[index];}
        constexpr const T& operator[](int index) const noexcept {return data[index];}

		friend std::ostream& operator<<(std::ostream& os, const vec<3, T> v) {
			os << "{x='" << v.x << "',y='" << v.y << "',z='" << v.z << "'}";
			return os;
		}
    };

    template <typename T> struct alignas(4 * sizeof(T)) vec<4, T> {
        union {
            struct { T x, y, z, w; };
            std::array<T, 4> data;
        };

        constexpr vec() noexcept : x(0), y(0), z(0), w(0) {}
        constexpr vec(T _x, T _y, T _z, T _w) noexcept : x(_x), y(_y), z(_z), w(_w) {}

        constexpr T& operator[](int index) noexcept {return data[index];}
        constexpr const T& operator[](int index) const noexcept {return data[index];}

		friend std::ostream& operator<<(std::ostream& os, const vec<4, T> v) {
			os << "{x='" << v.x << "',y='" << v.y << "',z='" << v.z << "',w='" << v.w << "'}";
			return os;
		}
    };

    // type definitions
    using vec2 = vec<2, float>;
    using vec3 = vec<3, float>;
    using vec4 = vec<4, float>;

}

#include "detail/vec_operators.inl"
