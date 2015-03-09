#include "Object3D.class.hpp"

//-/* CONSTRUCTORS / DESTRUCTORS */-//
/* CONSTRUCTOR */                      Object3D::Object3D(const unsigned int n_tri, const GLfloat* vbuff_data) :
  n_tri(n_tri), vbuffer(0)
{
  glGenBuffers(1, &(this->vbuffer));
  glBindBuffer(GL_ARRAY_BUFFER, this->vbuffer);
  glBufferData(GL_ARRAY_BUFFER, 9 * this->n_tri * sizeof(*(vbuff_data)), vbuff_data, GL_STATIC_DRAW);
}

/* DESTRUCTOR */                       Object3D::~Object3D(void)
{ }

//-/* FUNCTIONS */-//
void                                   Object3D::draw(void)
{
  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbuffer);
  glVertexAttribPointer(
                        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                        3,                  // size
                        GL_FLOAT,           // type
                        GL_FALSE,           // normalized?
                        0,                  // stride
                        (void*)0            // array buffer offset
                        );
  glDrawArrays(GL_TRIANGLES, 0, this->n_tri * 3);
  glDisableVertexAttribArray(0);
}

//-/* GETTERS / SETTERS */-//
