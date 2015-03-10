#ifndef  COLOREDOBJECT3D_CLASS_HPP
# define COLOREDOBJECT3D_CLASS_HPP

# include "openGL.hpp"
# include "Object3D.class.hpp"
# include "ShaderProgram.class.hpp"

class Object3D;
class ShaderProgram;

class ColoredObject3D : virtual public Object3D
{
public:
  //-/* CONSTRUCTORS / DESTRUCTORS */-//
  /* CONSTRUCTOR */                      ColoredObject3D(const glm::vec3& pos, const unsigned int n_tri, const GLfloat* vbuff_data, const GLfloat* cbuffer_data);
  virtual
  /* DESTRUCTOR */                       ~ColoredObject3D(void);

  //-/* FUCK CANONICAL MAYBE ? CALL ME MAYBE ? */-//
  /* CONSTRUCTOR */                      ColoredObject3D(void) = delete;
  /* CONSTRUCTOR */                      ColoredObject3D(const ColoredObject3D& src) = delete;
  ColoredObject3D&                       operator=(const ColoredObject3D& src) = delete;

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
  GLuint                                 cbuffer;

private:
  static
  ShaderProgram*                         _program;
};
/*                                     */
Object3D*                              newColoredTriangle(const glm::vec3& pos);
Object3D*                              newColoredCube(const glm::vec3& pos);

#endif
