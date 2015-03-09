#include "openGL.hpp"
#include "Object3D.class.hpp"
#include <iostream>

GLFWwindow* initOpenGL(void)
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

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
  }
  { // @note: additional settings
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  }

  return window;
}

GLuint      loadShaders(const char* vertex_fpath, const char* fragment_fpath);

int         main(void)
{
  GLFWwindow* window;
  Object3D*   obj;

  if ( (window = initOpenGL()) == NULL) {
    return -1;
  }

  obj = newTriangle();

  GLuint program_id = loadShaders("shaders/common/vertex.gl", "shaders/common/fragment.gl");
  glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program_id);

    obj->draw();

    glfwSwapBuffers(window);
    glfwPollEvents(); /* @todo: check events */
  } while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

  glDeleteProgram(program_id);
  glfwTerminate();
  return 0;
}
