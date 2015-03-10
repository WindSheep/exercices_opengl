#include "Object3D.class.hpp"
#include "Camera.class.hpp"

//-/* VARIABLE */-//
ShaderProgram*                         Object3D::_program = 0;

//-/* CONSTRUCTORS / DESTRUCTORS */-//
/* CONSTRUCTOR */                      Object3D::Object3D(const glm::vec3& pos, const unsigned int n_tri, const GLfloat* vbuff_data) :
  pos(pos), n_tri(n_tri), vbuffer(0)
{
  glGenBuffers(1, &(this->vbuffer));
  glBindBuffer(GL_ARRAY_BUFFER, this->vbuffer);
  glBufferData(GL_ARRAY_BUFFER, 9 * this->n_tri * sizeof(*(vbuff_data)), vbuff_data, GL_STATIC_DRAW);
}

/* DESTRUCTOR */                       Object3D::~Object3D(void)
{ glDeleteBuffers(1, &(this->vbuffer)); }

//-/* FUNCTIONS */-//
void                                   Object3D::draw(void)
{
  Object3D::s_getShaderProgram()->use();
  glm::mat4 model = glm::translate(glm::mat4(1.0f), this->pos);
  glm::mat4 mvp   = Camera::s_getCamera()->projection * Camera::s_getCamera()->view * model;
  Object3D::s_getShaderProgram()->modifyMVP(mvp);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbuffer);
  glVertexAttribPointer(
                        0,        // layout
                        3,        // size
                        GL_FLOAT, // type
                        GL_FALSE, // normalized?
                        0,        // stride
                        (void*)0  // array buffer offset
                        );

  glDrawArrays(GL_TRIANGLES, 0, this->n_tri * 3);
  glDisableVertexAttribArray(0);
}

//-/* GETTERS / SETTERS */-//
void                                   Object3D::s_setShaderProgram(ShaderProgram* program)
{ Object3D::_program = program; }

ShaderProgram*                         Object3D::s_getShaderProgram(void)
{ return Object3D::_program; }

const std::string&                     Object3D::s_getDirName(void)
{ static const std::string name = "object3d"; return name; }
