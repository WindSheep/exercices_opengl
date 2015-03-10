#ifndef  CAMERA_CLASS_HPP
# define CAMERA_CLASS_HPP

# include "openGL.hpp"

class Camera
{
public:
  //-/* CONSTRUCTORS / DESTRUCTORS */-//
  /* CONSTRUCTOR */                      Camera(const glm::mat4& view, const glm::mat4& projection);
  virtual
  /* DESTRUCTOR */                       ~Camera(void);

  //-/* FUCK CANONICAL MAYBE ? CALL ME MAYBE ? */-//
  /* CONSTRUCTOR */                      Camera(void) = delete;
  /* CONSTRUCTOR */                      Camera(const Camera& src) = delete;
  Camera&                                operator=(const Camera& src) = delete;

  //-/* FUNCTIONS */-//

  //-/* VARIABLES */-//
  glm::mat4                              view;
  glm::mat4                              projection;

  static
  void                                   s_setCamera(Camera* camera);
  static
  Camera*                                s_getCamera(void);

private:
  static
  Camera*                                _camera;
};
/*                                     */
Camera*                                newCamera(void);

#endif
