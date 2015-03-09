#ifndef  OBJECT3D_CLASS_HPP
# define OBJECT3D_CLASS_HPP

# include <GL/gl.h>

class Object3D
{
public:
  //-/* CONSTRUCTORS / DESTRUCTORS */-//
  /* CONSTRUCTOR */                      Object3D(void);
  virtual
  /* DESTRUCTOR */                       ~Object3D(void);

  //-/* FUCK CANONICAL MAYBE ? CALL ME MAYBE ? */-//
  // /* CONSTRUCTOR */                      Object3D(void) = delete;
  /* CONSTRUCTOR */                      Object3D(const Object3D& src) = delete;
  Object3D&                              operator=(const Object3D& src) = delete;

  //-/* FUNCTIONS */-//
  void                                   render(void);

  //-/* GETTERS / SETTERS */-//
  GLuint                                 getVertexBuffer(void) const;
  GLuint                                 getColorBuffer(void) const;

  //-/* VARIABLES */-//
  GLuint                                 vertexbuffer;
  GLuint                                 colorbuffer;
  unsigned int                           n_tri;

  //-/* FRIENDS */-//
  friend
  Object3D*                              newCube(void);
};

/*                                     */
Object3D*                              newCube(void);

#endif
