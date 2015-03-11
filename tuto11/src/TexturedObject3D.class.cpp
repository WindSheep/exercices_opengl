#include "TexturedObject3D.class.hpp"
#include "Camera.class.hpp"

ShaderProgram*                         TexturedObject3D::_program = 0;

//-/* CONSTRUCTORS / DESTRUCTORS */-//
/* CONSTRUCTOR */                      TexturedObject3D::TexturedObject3D(const glm::vec3& pos, const unsigned int n_tri, const GLfloat* vbuff_data, const GLfloat* uvbuff_data, Texture& texture) :
  Object3D(pos, n_tri, vbuff_data), _uvbuffer(0), _texture(texture)
{
  glGenBuffers(1, &(this->_uvbuffer));
  glBindBuffer(GL_ARRAY_BUFFER, this->_uvbuffer);
  glBufferData(GL_ARRAY_BUFFER, 9 * this->_n_tri * sizeof(*(uvbuff_data)), uvbuff_data, GL_STATIC_DRAW);
}

/* DESTRUCTOR */                       TexturedObject3D::~TexturedObject3D(void)
{ glDeleteBuffers(1, &(this->_uvbuffer)); }

//-/* FUNCTIONS */-//
void                                   TexturedObject3D::drawPart(void)
{
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, this->_uvbuffer);
  glVertexAttribPointer(
                        1,        // layout
                        2,        // size
                        GL_FLOAT, // type
                        GL_FALSE, // normalized
                        0,        // stride
                        (void*)0  // array buffer offset
                        );

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->_texture.getImageId());
  glUniform1i(this->_texture.getId(), 0);
}

void                                   TexturedObject3D::draw(void)
{
  if (TexturedObject3D::s_isInit() || TexturedObject3D::s_init()) {
    modifyMVP(*(TexturedObject3D::_program), *(Camera::s_getCamera()), this->_pos);

    Object3D::drawPart();
    this->drawPart();
    glDrawArrays(GL_TRIANGLES, 0, this->_n_tri * 3);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
  }
}

//-/* GETTERS / SETTERS */-//
bool                                   TexturedObject3D::s_init(void)
{
  if (!TexturedObject3D::s_isInit()) {
    const std::string dir = "shaders/texturedobject3d/";

    TexturedObject3D::_program =
      new ShaderProgram(dir + ShaderProgram::s_getVertexShaderName(),
                        dir + ShaderProgram::s_getFragmentShaderName());
  }
  return true;
}

bool                                   TexturedObject3D::s_isInit(void)
{ return TexturedObject3D::_program != NULL; }

void                                   TexturedObject3D::s_deInit(void)
{ delete TexturedObject3D::_program; TexturedObject3D::_program = NULL; }
