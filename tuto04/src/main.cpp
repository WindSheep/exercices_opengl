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
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  }

  return window;
}

void        moveCamera(GLuint program_id)
{
  // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
  glm::mat4 projection = glm::perspective(45.0f * static_cast<float>(M_PI) / 180.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  // @note: Camera lookAt(pos, toward, head)
  glm::mat4 view       = glm::lookAt(
                                     glm::vec3(4,3,3),
                                     glm::vec3(0,0,0),
                                     glm::vec3(0,1,0)
                                     );
  glm::mat4 model      = glm::mat4(1.0f);  // @note: identity
  glm::mat4 MVP        = projection * view * model; // @note: matrix multiplication is always reversed

  GLuint matrix_id = glGetUniformLocation(program_id, "MVP");
  glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &MVP[0][0]);
}

GLuint      loadShaders(const char* vertex_fpath, const char* fragment_fpath);

int         main(void)
{
  GLFWwindow* window;
  Object3D*   obj;

  if ( (window = initOpenGL()) == NULL) {
    return -1;
  }

  obj = newCube();

  GLuint program_id = loadShaders("shaders/common/vertex.gl", "shaders/common/fragment.gl");
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program_id);

    obj->draw();
    moveCamera(program_id); /* @todo: check if order is revelant */

    glfwSwapBuffers(window);
    glfwPollEvents(); /* @todo: check events */
  } while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

  glDeleteProgram(program_id);
  glfwTerminate();
  return 0;
}
