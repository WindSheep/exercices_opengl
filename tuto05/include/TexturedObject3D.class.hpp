#ifndef  TEXTUREDOBJECT3D_CLASS_HPP
# define TEXTUREDOBJECT3D_CLASS_HPP

# include "openGL.hpp"
# include "Object3D.class.hpp"
# include "Texture.class.hpp"
# include "ShaderProgram.class.hpp"

class Object3D;
class ShaderProgram;
class Texture;

class TexturedObject3D : virtual public Object3D
{
public:
  //-/* CONSTRUCTORS / DESTRUCTORS */-//
  /* CONSTRUCTOR */                      TexturedObject3D(const glm::vec3& pos, const unsigned int n_tri, const GLfloat* vbuff_data, const GLfloat* uvbuffer_data, Texture& texture);
  virtual
  /* DESTRUCTOR */                       ~TexturedObject3D(void);

  //-/* FUCK CANONICAL MAYBE ? CALL ME MAYBE ? */-//
  /* CONSTRUCTOR */                      TexturedObject3D(void) = delete;
  /* CONSTRUCTOR */                      TexturedObject3D(const TexturedObject3D& src) = delete;
  TexturedObject3D&                      operator=(const TexturedObject3D& src) = delete;

  //-/* FUNCTIONS */-//
  virtual
  void                                   draw(void);

  //-/* GETTERS / SETTERS */-//
  static
  void                                   s_setShaderProgram(ShaderProgram* program);

  static
  ShaderProgram*                         s_getShaderProgram(void);

  static
  const std::string&                     s_getDirName(void);

  //-/* VARIABLES */-//
  GLuint                                 uvbuffer;
  Texture&                               texture;

  static
  ShaderProgram*                         _program;
};
/*                                     */
Object3D*                              newTexturedTriangle(const glm::vec3& pos);
Object3D*                              newTexturedCube(const glm::vec3& pos);

#endif
