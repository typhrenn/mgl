#pragma once

#include "../core/mat.hpp"
#include "../core/vec.hpp"
#include "quat_func.hpp"

namespace mgl {
    // creates a 4x4 transformation matrix
    inline mat4x4 transform_mat4x4(const vec3 &transl, const vec3 &scale, const vec3 &rot) noexcept {
        mat4x4 res = quat_to_mat4x4(full_axis_quat(rot));

        for (int c = 0; c < 3; ++c) {
            res[c][0] *= scale[c];
            res[c][1] *= scale[c];
            res[c][2] *= scale[c];
        }

        res[3][0] = transl.x;
        res[3][1] = transl.y;
        res[3][2] = transl.z;
        res[3][3] = 1.0f;

        return res;
    }

    inline mat4x4 transform_mat4x4(const vec3 &transl, const vec3 &scale, const quat<float> &q) noexcept {
        mat4x4 res = quat_to_mat4x4(q);

        for (int c = 0; c < 3; ++c) {
            res[c][0] *= scale[c];
            res[c][1] *= scale[c];
            res[c][2] *= scale[c];
        }

        res[3][0] = transl.x;
        res[3][1] = transl.y;
        res[3][2] = transl.z;
        res[3][3] = 1.0f;

        return res;
    }

}
