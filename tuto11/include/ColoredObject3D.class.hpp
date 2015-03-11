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
  bool                                   s_init(void);

  static
  void                                   s_deInit(void);

  static
  bool                                   s_isInit(void);

protected:
  void                                   drawPart(void);

private:
  //-/* VARIABLES */-//
  GLuint                                 _cbuffer;

  static
  ShaderProgram*                         _program;
};
/*                                     */
Object3D*                              newColoredTriangle(const glm::vec3& pos);
Object3D*                              newColoredCube(const glm::vec3& pos);

#endif
