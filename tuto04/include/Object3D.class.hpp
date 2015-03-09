#ifndef  OBJECT3D_CLASS_HPP
# define OBJECT3D_CLASS_HPP

# include "openGL.hpp"

class Object3D
{
public:
  //-/* CONSTRUCTORS / DESTRUCTORS */-//
  /* CONSTRUCTOR */                      Object3D(const unsigned int n_tri, const GLfloat* vbuff_data, const GLfloat* cbuffer_data);
  virtual
  /* DESTRUCTOR */                       ~Object3D(void);

  //-/* FUCK CANONICAL MAYBE ? CALL ME MAYBE ? */-//
  /* CONSTRUCTOR */                      Object3D(void) = delete;
  /* CONSTRUCTOR */                      Object3D(const Object3D& src) = delete;
  Object3D&                              operator=(const Object3D& src) = delete;

  //-/* FUNCTIONS */-//
  void                                   draw(void);

  //-/* GETTERS / SETTERS */-//

  //-/* VARIABLES */-//
  const unsigned int                     n_tri;
  GLuint                                 vbuffer;
  GLuint                                 cbuffer;

  //-/* FRIENDS */-//
};

/*                                     */
Object3D*                              newTriangle(void);
Object3D*                              newCube(void);

#endif
