#include "openGL.hpp"
#include "Camera.class.hpp"
#include "Object3D.class.hpp"
#include "TexturedObject3D.class.hpp"
#include "ColoredObject3D.class.hpp"

#include <iostream>
#include <cstdlib>

static GLuint g_vertex_array_id = 0;

GLFWwindow*   initOpenGL(void)
{
  GLFWwindow* window;
  { // @note: initialize openGL
    if (glfwInit() == GL_FALSE) {
      std::printf("glfwInit() failed\n");
      return NULL;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); /* @note: anti-aliasing */
    /* @note: openGL 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); /* @note: for MacOsX */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  }
  { // @note: create window
    window = glfwCreateWindow(1024, 768, "OpenGL Window", NULL, NULL);
    if (window == NULL) {
      std::cerr << "Failed to open GLFW window." << std::endl;
      glfwTerminate();
      return NULL;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true; // @note: Needed in core profile
    if (glewInit() != GLEW_OK) {
      std::cerr << "Failed to initialize GLEW" << std::endl;
      glfwTerminate();
      return NULL;
    }

    GLuint vertex_array_id;
    glGenVertexArrays(1, &(vertex_array_id));
    glBindVertexArray(vertex_array_id);
    g_vertex_array_id = vertex_array_id; /* @note: to do, to be changed */
  }
  { // @note: additional settings
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  }

  return window;
}

bool          constructPrograms(void)
{
  const std::string dir = "shaders";

  ShaderProgram* program_obj = new ShaderProgram(dir + "/" + Object3D::s_getDirName() + "/" + ShaderProgram::s_getVertexShaderName(),
                                                 dir + "/" + Object3D::s_getDirName() + "/" + ShaderProgram::s_getFragmentShaderName());

  ShaderProgram* program_cobj = new ShaderProgram(dir + "/" + ColoredObject3D::s_getDirName() + "/" + ShaderProgram::s_getVertexShaderName(),
                                                  dir + "/" + ColoredObject3D::s_getDirName() + "/"+ ShaderProgram::s_getFragmentShaderName());

  ShaderProgram* program_tobj = new ShaderProgram(dir + "/" + TexturedObject3D::s_getDirName() + "/"+ ShaderProgram::s_getVertexShaderName(),
                                                  dir + "/" + TexturedObject3D::s_getDirName() + "/"+ ShaderProgram::s_getFragmentShaderName());

  Object3D::s_setShaderProgram(program_obj);
  ColoredObject3D::s_setShaderProgram(program_cobj);
  TexturedObject3D::s_setShaderProgram(program_tobj);
  return true;
}

void          destructPrograms(void)
{
  delete Object3D::s_getShaderProgram();
  delete ColoredObject3D::s_getShaderProgram();
  delete TexturedObject3D::s_getShaderProgram();
}

void          constructCamera(void)
{
  Camera* camera = newCamera();
  Camera::s_setCamera(camera);
}

void          destructCamera(void)
{
  delete Camera::s_getCamera();
}

int           main(void)
{
  GLFWwindow* window;
  Camera*     camera;
  Object3D*   obj1;
  Object3D*   obj2;
  glm::vec3   pos1(0.0f, 0.0f, 0.0f);
  glm::vec3   pos2(0.0f, 0.0f, -5.0f);

  if ( (window = initOpenGL()) == NULL) {
    return -1;
  }

  constructPrograms();
  constructCamera();
  obj1 = newColoredTriangle(pos1);
  obj2 = newTexturedCube(pos2);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    obj1->draw();
    obj2->draw();

    glfwSwapBuffers(window);
    glfwPollEvents(); /* @todo: check events */

  } while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

  delete obj1;
  delete obj2;
  destructCamera();
  destructPrograms();

  glDeleteVertexArrays(1, &(g_vertex_array_id));
  glfwTerminate();
  return 0;
}
