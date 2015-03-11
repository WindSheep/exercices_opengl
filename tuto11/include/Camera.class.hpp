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
  const glm::mat4&                       getView(void) const;
  const glm::mat4&                       getProjection(void) const;

  //-/* GETTERS / SETTERS */-//
  static
  void                                   s_setCamera(Camera* camera);
  static
  Camera*                                s_getCamera(void);

protected:
  //-/* VARIABLES */-//
  glm::mat4                              _view;
  glm::mat4                              _projection;

private:
  static
  Camera*                                _camera;
};
/*                                     */
Camera*                                newCamera(void);
// Camera*                                g_camera;

#endif
