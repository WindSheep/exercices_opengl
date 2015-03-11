#include "ColoredObject3D.class.hpp"
#include "Camera.class.hpp"

ShaderProgram*                         ColoredObject3D::_program = 0;

//-/* CONSTRUCTORS / DESTRUCTORS */-//
/* CONSTRUCTOR */                      ColoredObject3D::ColoredObject3D(const glm::vec3& pos, const unsigned int n_tri, const GLfloat* vbuff_data, const GLfloat* cbuff_data) :
  Object3D(pos, n_tri, vbuff_data), _cbuffer(0)
{
  glGenBuffers(1, &(this->_cbuffer));
  glBindBuffer(GL_ARRAY_BUFFER, this->_cbuffer);
  glBufferData(GL_ARRAY_BUFFER, 9 * this->_n_tri * sizeof(*(cbuff_data)), cbuff_data, GL_STATIC_DRAW);
}

/* DESTRUCTOR */                       ColoredObject3D::~ColoredObject3D(void)
{ glDeleteBuffers(1, &(this->_cbuffer)); }

//-/* FUNCTIONS */-//
void                                   ColoredObject3D::drawPart(void)
{
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, this->_cbuffer);
  glVertexAttribPointer(
                        1,        // layout
                        3,        // size
                        GL_FLOAT, // type
                        GL_FALSE, // normalized
                        0,        // stride
                        (void*)0  // array_buffer offset
                        );
}

void                                   ColoredObject3D::draw(void)
{
  if (ColoredObject3D::s_isInit() || ColoredObject3D::s_init()) {
    modifyMVP(*(ColoredObject3D::_program), *(Camera::s_getCamera()), this->_pos);

    Object3D::drawPart();
    this->drawPart();
    glDrawArrays(GL_TRIANGLES, 0, this->_n_tri * 3);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
  }
}

//-/* GETTERS / SETTERS */-//
bool                                   ColoredObject3D::s_init(void)
{
  if (!ColoredObject3D::s_isInit()) {
    const std::string dir = "shaders/coloredobject3d/";

    ColoredObject3D::_program =
      new ShaderProgram(dir + ShaderProgram::s_getVertexShaderName(),
                        dir + ShaderProgram::s_getFragmentShaderName());
  }
  return true;
}

bool                                   ColoredObject3D::s_isInit(void)
{ return ColoredObject3D::_program != NULL; }

void                                   ColoredObject3D::s_deInit(void)
{ delete ColoredObject3D::_program; ColoredObject3D::_program = NULL; }
