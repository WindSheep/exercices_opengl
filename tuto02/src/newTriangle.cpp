#include "Object3D.class.hpp"

Object3D* newTriangle(void)
{
  static const GLfloat vertexbuffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
  };

  return new Object3D(1, vertexbuffer_data);
}
