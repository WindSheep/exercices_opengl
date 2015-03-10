#include "TexturedObject3D.class.hpp"
#include "Camera.class.hpp"

ShaderProgram*                         TexturedObject3D::_program = 0;

//-/* CONSTRUCTORS / DESTRUCTORS */-//
/* CONSTRUCTOR */                      TexturedObject3D::TexturedObject3D(const glm::vec3& pos, const unsigned int n_tri, const GLfloat* vbuff_data, const GLfloat* uvbuff_data, Texture& texture) :
  Object3D(pos, n_tri, vbuff_data), uvbuffer(0), texture(texture)
{
  glGenBuffers(1, &(this->uvbuffer));
  glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
  glBufferData(GL_ARRAY_BUFFER, 9 * this->n_tri * sizeof(*(uvbuff_data)), uvbuff_data, GL_STATIC_DRAW);
}

/* DESTRUCTOR */                       TexturedObject3D::~TexturedObject3D(void)
{ glDeleteBuffers(1, &(this->uvbuffer)); }

//-/* FUNCTIONS */-//
void                                   TexturedObject3D::draw(void)
{
  TexturedObject3D::s_getShaderProgram()->use();
  glm::mat4 model = glm::translate(glm::mat4(1.0f), this->pos);
  glm::mat4 mvp   = Camera::s_getCamera()->projection * Camera::s_getCamera()->view * model;
  TexturedObject3D::s_getShaderProgram()->modifyMVP(mvp);

  // Activate texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->texture.image_id);
  glUniform1i(this->texture.texture_id, 0);

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

  // 2nd attribute buffer : texture
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
  glVertexAttribPointer(
                        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                        2,                                // size
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
void                                   TexturedObject3D::s_setShaderProgram(ShaderProgram* program)
{ TexturedObject3D::_program = program; }

ShaderProgram*                         TexturedObject3D::s_getShaderProgram(void)
{ return TexturedObject3D::_program; }

const std::string&                     TexturedObject3D::s_getDirName(void)
{ static const std::string name = "texturedobject3d"; return name; }
