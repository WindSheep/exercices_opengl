#include "opengl.hpp"
#include "camera.class.hpp"
#include "object3d.class.hpp"
#include "coloredobject3d.class.hpp"
#include "selector2d.class.hpp"
#include "texturedobject3d.class.hpp"
#include "text2d.class.hpp"

#include <iostream>
#include <cstdlib>

static GLuint g_vertex_array_id = 0;

GLFWwindow*   initOpenGL(void) {
    GLFWwindow* window; {

        // @note: initialize openGL
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
    {
        // @note: create window
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
    {
        // @note: additional settings
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    }

    return window;
}

void constructCamera(void) {
    Camera* camera = newCamera();
    Camera::s_setCamera(camera);
}

void destructCamera(void) {
    delete Camera::s_getCamera();
}

bool loadOBJ(const char* path,
             std::vector<glm::vec3>& out_vertices,
             std::vector<glm::vec2>& out_uvs,
             std::vector<glm::vec3>& out_normals);

Object3D* test(const glm::vec3& pos) {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals; // Won't be used at the moment.
    bool res;

    res = loadOBJ("objects/cube.obj", vertices, uvs, normals);
    if (res == false) {
        return NULL;
    }
    // glBufferData(GL_ARRAY_BUFFER, 9 * this->_n_tri * sizeof(*(vbuff_data)), vbuff_data, GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    return new Object3D(pos, vertices.size() / 3, &(vertices[0][0]));
}

int main(void) {
    GLFWwindow* window;
    Camera*     camera;
    Object3D*   obj1;
    Object3D*   obj2;
    Object3D*   obj3;
    Selector2D* selector;
    glm::vec3   pos1(0.0f, 0.0f, 0.0f);
    glm::vec3   pos2(-4.0f, 1.0f, -5.0f);
    glm::vec3   pos3(0.0f, 0.0f, -5.0f);

    (void)pos3;
    if ( (window = initOpenGL()) == NULL) {
        return -1;
    }

    constructCamera();
    Object3D::s_init();
    ColoredObject3D::s_init();
    TexturedObject3D::s_init();
    Text2D::s_init();

    obj1 = newColoredTriangle(pos1);
    obj2 = newTexturedCube(pos2);
    obj3 = test(pos3);
    selector = newDefaultSelector2D();

    glClearColor(0.01f, 0.01f, 0.01f, 0);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);

    int keystate_up   = GLFW_KEY_UNKNOWN;
    int keystate_down = GLFW_KEY_UNKNOWN;
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        obj1->draw();
        obj2->draw();
        obj3->draw();
        selector->draw();

        glfwSwapBuffers(window);
        glfwPollEvents(); /* @todo: check events */

        if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
            std::cout << selector->getValue() << std::endl;
            break;
        }
        else {
            int state;

            state = glfwGetKey(window, GLFW_KEY_UP);
            if (state != keystate_up) {
                keystate_up = state;
                if (state == GLFW_PRESS) {
                    selector->next();
                }
            }

            state = glfwGetKey(window, GLFW_KEY_DOWN);
            if (state != keystate_down) {
                keystate_down = state;
                if (state == GLFW_PRESS) {
                    selector->previous();
                }
            }
        }

    } while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

    delete obj1;
    delete obj2;
    delete obj3;
    delete selector;
    Object3D::s_deInit();
    ColoredObject3D::s_deInit();
    TexturedObject3D::s_deInit();
    Text2D::s_deInit();
    destructCamera();

    glfwDestroyWindow(window);
    glDeleteVertexArrays(1, &(g_vertex_array_id));
    glfwTerminate();
    return 0;
}
