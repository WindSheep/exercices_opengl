#include "object3d.class.hpp"

Object3D* newTriangle(const glm::vec3& pos) {
    static const GLfloat vertexbuffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    return new Object3D(pos, 1, vertexbuffer_data);
}
