#include "openGL.hpp"
#include "ShaderProgram.class.hpp"
#include "Camera.class.hpp"

void modifyMVP(ShaderProgram& program, const Camera& camera, const glm::vec3& pos)
{
  program.use();
  glm::mat4 model = glm::translate(glm::mat4(1.0f), pos);
  glm::mat4 mvp   = camera.getProjection() * camera.getView() * model;
  program.modifyMVP(mvp);
}
