#include "camera.class.hpp"

Camera* Camera::_camera = NULL;

// /* CTOR */ Camera::Camera(const glm::mat4& view, const glm::mat4& projection) :
//     _view(view), _projection(projection) {
// }

/* CTOR */ Camera::Camera(const glm::vec3& camera_pos,
                          const glm::vec3& camera_look_at,
                          const glm::vec3& camera_head_up,
                          float fov_rad,
                          /* to be removed */
                          float win_width,
                          float win_height,
                          /* to be removed */
                          float near_clipping_plane,
                          float far_clipping_plane) :
    _camera_pos(camera_pos),
    _camera_look_at(camera_look_at),
    _camera_head_up(camera_head_up),
    _fov_rad(fov_rad),
    /* to be removed */
    _win_width(win_width),
    _win_height(win_height),
    /* to be removed */
    _near_clipping_plane(near_clipping_plane),
    _far_clipping_plane(far_clipping_plane),
    _view(glm::lookAt(
                      this->_camera_pos,
                      this->_camera_look_at,
                      this->_camera_head_up
                      )),
    _projection(glm::perspective(this->_fov_rad,
                                 this->_win_width / this->_win_height,
                                 this->_near_clipping_plane,
                                 this->_far_clipping_plane))
{
}

/* DTOR */ Camera::~Camera(void) {
}

void Camera::modifyMVP(ShaderProgram& program,
                       const glm::vec3& pos) {
    GLuint    uniform_id;

    uniform_id = glGetUniformLocation(program.getId(), "FOV");
    glUniform1fv(uniform_id, 1, &(this->_fov_rad));

    uniform_id = glGetUniformLocation(program.getId(), "WIN_WIDTH");
    glUniform1fv(uniform_id, 1, &(this->_win_width));

    uniform_id = glGetUniformLocation(program.getId(), "WIN_HEIGHT");
    glUniform1fv(uniform_id, 1, &(this->_win_height));

    uniform_id = glGetUniformLocation(program.getId(), "NEAR_CLIPPING_PLANE");
    glUniform1fv(uniform_id, 1, &(this->_near_clipping_plane));

    uniform_id = glGetUniformLocation(program.getId(), "FAR_CLIPPING_PLANE");
    glUniform1fv(uniform_id, 1, &(this->_far_clipping_plane));

    uniform_id = glGetUniformLocation(program.getId(), "CAMERA_POS");
    glUniform3fv(uniform_id, 1, &(this->_camera_pos[0]));

    uniform_id = glGetUniformLocation(program.getId(), "CAMERA_LOOK_AT");
    glUniform3fv(uniform_id, 1, &(this->_camera_look_at[0]));

    uniform_id = glGetUniformLocation(program.getId(), "CAMERA_HEAD_UP");
    glUniform3fv(uniform_id, 1, &(this->_camera_head_up[0]));

    uniform_id = glGetUniformLocation(program.getId(), "MODEL_POS");
    glUniform3fv(uniform_id, 1, &(pos[0]));
}

/* SETTERS && GETTERS {{{ */
void Camera::s_setCamera(Camera* camera) {
    Camera::_camera = camera;
}

Camera* Camera::s_getCamera(void) {
    return Camera::_camera;
}
/* SETTERS && GETTERS }}} */

Camera* newCamera(void) {
    /* view */
    glm::vec3 camera_pos = glm::vec3(4,3,3);
    glm::vec3 camera_look_at = glm::vec3(0,0,0);
    glm::vec3 camera_head_up = glm::vec3(0,1,0);
    /* projection */
    float     fov_deg = 45.0f;
    float     fov_rad = fov_deg * static_cast<float>(M_PI) / 180.0f;
    float     win_width = 1024;
    float     win_height = 768;
    float     near_clipping_plane = 0.1f;
    float     far_clipping_plane = 100.0f;

    // // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    // glm::mat4 projection = glm::perspective(,
    //                                         4.0f / 3.0f, 0.1f, 100.0f);
    // // @note: Camera lookAt(pos, toward, head)
    // glm::mat4 view       = glm::lookAt(
    //                                    glm::vec3(4,3,3),
    //                                    glm::vec3(0,0,0),
    //                                    glm::vec3(0,1,0)
    //                                    );

    // return new Camera(view, projection);
    return new Camera(camera_pos,
                      camera_look_at,
                      camera_head_up,
                      fov_rad,
                      /* to be removed */
                      win_width,
                      win_height,
                      /* to be removed */
                      near_clipping_plane,
                      far_clipping_plane);
}
