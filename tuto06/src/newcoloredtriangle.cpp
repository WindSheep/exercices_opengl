#include "coloredobject3d.class.hpp"

Object3D* newColoredTriangle(const glm::vec3& pos) {
    static const GLfloat vertexbuffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    static const GLfloat colorbuffer_data[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
    };

    return new ColoredObject3D(pos, 1, vertexbuffer_data, colorbuffer_data);
}
