#include "mgl.hpp" // Assuming this includes your headers
#include <vector>
#include <iostream>

struct Cube {
    std::vector<mgl::vec3> v;
};

Cube rot_cube_quat(Cube c, const mgl::vec3& r) {
    mgl::quat_f q = mgl::full_axis_quat(r);

    for (auto &vertex : c.v) {
        vertex = mgl::rotate(q, vertex);
    }

    return c;
}

Cube rot_cube_mat(Cube c, const mgl::vec3& r) {
    mgl::quat_f q = mgl::full_axis_quat(r);
    
    mgl::mat4x4 rot_matrix = mgl::quat_to_mat4x4(q);

    for (auto &vertex : c.v) {
        vertex = mgl::transform_point(rot_matrix, vertex);
    }

    return c;
}

int main() {
    Cube c;

    c.v.push_back({-1.0f, -1.0f, -1.0f});
    c.v.push_back({-1.0f,  1.0f, -1.0f});
    c.v.push_back({ 1.0f, -1.0f, -1.0f});
    c.v.push_back({ 1.0f,  1.0f, -1.0f});
    c.v.push_back({-1.0f, -1.0f,  1.0f});
    c.v.push_back({-1.0f,  1.0f,  1.0f});
    c.v.push_back({ 1.0f, -1.0f,  1.0f});
    c.v.push_back({ 1.0f,  1.0f,  1.0f});

    mgl::vec3 rotation_radians = {3.14159f, 0.87266f, 0.87266f}; 

    Cube c_quat = rot_cube_quat(c, rotation_radians);

    Cube c_mat = rot_cube_mat(c, rotation_radians);

    std::cout << "rotated vertices:\n";
    for (const auto& vertex : c_mat.v) {
        std::cout << "[" << vertex.x << ", " << vertex.y << ", " << vertex.z << "]\n";
    }

    return 0;
}