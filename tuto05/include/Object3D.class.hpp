#ifndef  OBJECT3D_CLASS_HPP
# define OBJECT3D_CLASS_HPP

# include "openGL.hpp"
# include "ShaderProgram.class.hpp"

class ShaderProgram;

class Object3D
{
public:
  //-/* CONSTRUCTORS / DESTRUCTORS */-//
  /* CONSTRUCTOR */                      Object3D(const glm::vec3& pos, const unsigned int n_tri, const GLfloat* vbuff_data);
  virtual
  /* DESTRUCTOR */                       ~Object3D(void);

  //-/* FUCK CANONICAL MAYBE ? CALL ME MAYBE ? */-//
  /* CONSTRUCTOR */                      Object3D(void) = delete;
  /* CONSTRUCTOR */                      Object3D(const Object3D& src) = delete;
  Object3D&                              operator=(const Object3D& src) = delete;

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
  const glm::vec3&                       pos;
  const unsigned int                     n_tri;
  GLuint                                 vbuffer;

private:
  static
  ShaderProgram*                         _program;
};
/*                                       */
Object3D*                                newTriangle(const glm::vec3& pos);
Object3D*                                newCube(const glm::vec3& pos);

#endif
