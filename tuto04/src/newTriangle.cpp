#include "Object3D.class.hpp"

Object3D* newTriangle(void)
{
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

  return new Object3D(1, vertexbuffer_data, colorbuffer_data);
}
