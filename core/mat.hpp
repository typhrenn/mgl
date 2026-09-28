#pragma once

#include <array>
#include "vec.hpp"

namespace mgl {
    template <int C, int R, typename T>
    struct mat {
        std::array<vec<R, T>, C> columns;

        static constexpr int cols = C;
        static constexpr int rows = R;

        constexpr mat() noexcept {for (int i = 0; i < C; ++i) columns[i] = vec<R, T>{};}
        constexpr mat(T n) noexcept {for (int c = 0; c < C; ++c) {for (int r = 0; r < R; ++r) {columns[c][r] = n;}}}
        constexpr mat(std::initializer_list<T> init) noexcept {auto it = init.begin(); for (int c = 0; c < C; ++c) {for (int r = 0; r < R; ++r) {if (it != init.end()) {columns[c][r] = *it++;}}}}

        constexpr vec<R, T>& operator[](int index) noexcept {return columns[index];}
        constexpr const vec<R, T>& operator[](int index) const noexcept {return columns[index];}

        constexpr const T* data() const noexcept {return &columns[0][0];}
    };

    // type definitions
    template <int C, int R, typename T = float>
	using mat_t = mat<C, R, T>;

    using mat1x2 = mat_t<1, 2>;
    using mat1x3 = mat_t<1, 3>;
    using mat1x4 = mat_t<1, 4>;

    using mat2x1 = mat_t<2, 1>;
    using mat2x2 = mat_t<2, 2>;
    using mat2x3 = mat_t<2, 3>;
    using mat2x4 = mat_t<2, 4>;

    using mat3x1 = mat_t<3, 1>;
    using mat3x2 = mat_t<3, 2>;
    using mat3x3 = mat_t<3, 3>;
    using mat3x4 = mat_t<3, 4>;

    using mat4x1 = mat_t<4, 1>;
    using mat4x2 = mat_t<4, 2>;
    using mat4x3 = mat_t<4, 3>;
    using mat4x4 = mat_t<4, 4>;
}

#include "detail/mat_operators.inl"
