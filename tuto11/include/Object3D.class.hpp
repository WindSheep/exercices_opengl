#ifndef  OBJECT3D_CLASS_HPP
# define OBJECT3D_CLASS_HPP

# include "openGL.hpp"
# include "ShaderProgram.class.hpp"

class Camera;
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
  bool                                   s_init(void);

  static
  void                                   s_deInit(void);

  static
  bool                                   s_isInit(void);

protected:
  //-/* FUNCTIONS */-//
  void                                   drawPart(void);

  //-/* VARIABLES */-//
  glm::vec3                              _pos;
  const unsigned int                     _n_tri;

private:
  //-/* VARIABLES */-//
  GLuint                                 _vbuffer;

  static
  ShaderProgram*                         _program;
};
/*                                     */
Object3D*                              newTriangle(const glm::vec3& pos);
Object3D*                              newCube(const glm::vec3& pos);

void                                   modifyMVP(ShaderProgram& program, const Camera& camera, const glm::vec3& pos);

#endif
