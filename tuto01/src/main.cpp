#include "openGL.hpp"
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
  }
  { // @note: additional settings
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  }

  return window;
}

int         main(void)
{
  GLFWwindow* window;

  if ( (window = initOpenGL()) == NULL) {
    return -1;
  }

  do {
    glfwSwapBuffers(window);
    glfwPollEvents(); /* @todo: check events */
  } while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

  glfwTerminate();
  return 0;
}
