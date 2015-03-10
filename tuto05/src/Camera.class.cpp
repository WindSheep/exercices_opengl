# include "Camera.class.hpp"

//-/* VARIABLES */-//
Camera*                                Camera::_camera = NULL;

//-/* CONSTRUCTORS / DESTRUCTORS */-//
/* CONSTRUCTOR */                      Camera::Camera(const glm::mat4& view, const glm::mat4& projection) :
  view(view), projection(projection)
{ }

/* DESTRUCTOR */                       Camera::~Camera(void)
{ }

//-/* SETTERS / GETTERS */-//
void                                   Camera::s_setCamera(Camera* camera)
{ Camera::_camera = camera; }

Camera*                                Camera::s_getCamera(void)
{ return Camera::_camera; }

Camera*                                newCamera(void)
{
  // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
  glm::mat4 projection = glm::perspective(45.0f * static_cast<float>(M_PI) / 180.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  // @note: Camera lookAt(pos, toward, head)
  glm::mat4 view       = glm::lookAt(
                                     glm::vec3(4,3,3),
                                     glm::vec3(0,0,0),
                                     glm::vec3(0,1,0)
                                     );

  return new Camera(view, projection);
}
