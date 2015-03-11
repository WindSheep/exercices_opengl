#include "Object3D.class.hpp"
#include "Camera.class.hpp"

//-/* VARIABLE */-//
ShaderProgram*                         Object3D::_program = 0;

//-/* CONSTRUCTORS / DESTRUCTORS */-//
/* CONSTRUCTOR */                      Object3D::Object3D(const glm::vec3& pos, const unsigned int n_tri, const GLfloat* vbuff_data) :
  _pos(pos), _n_tri(n_tri), _vbuffer(0)
{
  glGenBuffers(1, &(this->_vbuffer));
  glBindBuffer(GL_ARRAY_BUFFER, this->_vbuffer);
  glBufferData(GL_ARRAY_BUFFER, 9 * this->_n_tri * sizeof(*(vbuff_data)), vbuff_data, GL_STATIC_DRAW);
// this->_n_tri * 3
}

/* DESTRUCTOR */                       Object3D::~Object3D(void)
{ glDeleteBuffers(1, &(this->_vbuffer)); }

//-/* FUNCTIONS */-//
void                                   Object3D::drawPart(void)
{
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, this->_vbuffer);
  glVertexAttribPointer(
                        0,        // layout
                        3,        // size
                        GL_FLOAT, // type
                        GL_FALSE, // normalized
                        0,        // stride
                        (void*)0  // array_buffer offset
                        );
}

void                                   Object3D::draw(void)
{
  if (Object3D::s_isInit() || Object3D::s_init()) {
    modifyMVP(*(Object3D::_program), *(Camera::s_getCamera()), this->_pos);

    this->drawPart();
    glDrawArrays(GL_TRIANGLES, 0, this->_n_tri * 3);
    glDisableVertexAttribArray(0);
  }
}

//-/* GETTERS / SETTERS */-//
bool                                   Object3D::s_init(void)
{
  if (!Object3D::s_isInit()) {
    const std::string dir = "shaders/object3d/";

    Object3D::_program =
      new ShaderProgram(dir + ShaderProgram::s_getVertexShaderName(),
                        dir + ShaderProgram::s_getFragmentShaderName());
  }
  return true;
}

bool                                   Object3D::s_isInit(void)
{ return Object3D::_program != NULL; }

void                                   Object3D::s_deInit(void)
{ delete Object3D::_program; Object3D::_program = NULL; }
