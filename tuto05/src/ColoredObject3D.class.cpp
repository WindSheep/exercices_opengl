#include "ColoredObject3D.class.hpp"
#include "Camera.class.hpp"

ShaderProgram*                         ColoredObject3D::_program = 0;

//-/* CONSTRUCTORS / DESTRUCTORS */-//
/* CONSTRUCTOR */                      ColoredObject3D::ColoredObject3D(const glm::vec3& pos, const unsigned int n_tri, const GLfloat* vbuff_data, const GLfloat* cbuff_data) :
  Object3D(pos, n_tri, vbuff_data), cbuffer(0)
{
  glGenBuffers(1, &(this->cbuffer));
  glBindBuffer(GL_ARRAY_BUFFER, this->cbuffer);
  glBufferData(GL_ARRAY_BUFFER, 9 * this->n_tri * sizeof(*(cbuff_data)), cbuff_data, GL_STATIC_DRAW);
}

/* DESTRUCTOR */                       ColoredObject3D::~ColoredObject3D(void)
{ glDeleteBuffers(1, &(this->cbuffer)); }

//-/* FUNCTIONS */-//
void                                   ColoredObject3D::draw(void)
{
  ColoredObject3D::s_getShaderProgram()->use();
  /* @todo: add */
  ColoredObject3D::s_getShaderProgram()->use();
  glm::mat4 model = glm::translate(glm::mat4(1.0f), this->pos);
  glm::mat4 mvp   = Camera::s_getCamera()->projection * Camera::s_getCamera()->view * model;
  ColoredObject3D::s_getShaderProgram()->modifyMVP(mvp);

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

  // 2nd attribute buffer : colors
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, this->cbuffer);
  glVertexAttribPointer(
                        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                        3,                                // size
                        GL_FLOAT,                         // type
                        GL_FALSE,                         // normalized?
                        0,                                // stride
                        (void*)0                          // array buffer offset
                        );

  glDrawArrays(GL_TRIANGLES, 0, this->n_tri * 3);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
}

//-/* GETTERS / SETTERS */-//
void                                   ColoredObject3D::s_setShaderProgram(ShaderProgram* program)
{ ColoredObject3D::_program = program; }

ShaderProgram*                         ColoredObject3D::s_getShaderProgram(void)
{ return ColoredObject3D::_program; }

const std::string&                     ColoredObject3D::s_getDirName(void)
{ static const std::string name = "coloredobject3d"; return name; }
