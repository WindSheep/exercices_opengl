#include "camera.class.hpp"

Camera* Camera::_camera = NULL;
extern float win_width;
extern float win_height;

/* CTOR */ Camera::Camera(const glm::vec3& pos,
                          const glm::vec3& look_at,
                          const glm::vec3& head_up,
                          float fov_rad,
                          float near_clipping_plane,
                          float far_clipping_plane) :
    _pos(pos),
    _look_at(look_at),
    _head_up(head_up),
    _fov_rad(fov_rad),
    _near_clipping_plane(near_clipping_plane),
    _far_clipping_plane(far_clipping_plane)
{
}

/* DTOR */ Camera::~Camera(void) {
}

void Camera::modifyMVP(ShaderProgram& program,
                       const glm::vec3& pos) {
    GLuint    uniform_id;

    uniform_id = glGetUniformLocation(program.getId(), "WIN_WIDTH");
    glUniform1fv(uniform_id, 1, &(win_width));

    uniform_id = glGetUniformLocation(program.getId(), "WIN_HEIGHT");
    glUniform1fv(uniform_id, 1, &(win_height));

    uniform_id = glGetUniformLocation(program.getId(), "CAMERA_FOV");
    glUniform1fv(uniform_id, 1, &(this->_fov_rad));

    uniform_id = glGetUniformLocation(program.getId(), "CAMERA_NEAR_CLIPPING_PLANE");
    glUniform1fv(uniform_id, 1, &(this->_near_clipping_plane));

    uniform_id = glGetUniformLocation(program.getId(), "CAMERA_FAR_CLIPPING_PLANE");
    glUniform1fv(uniform_id, 1, &(this->_far_clipping_plane));

    uniform_id = glGetUniformLocation(program.getId(), "CAMERA_POS");
    glUniform3fv(uniform_id, 1, &(this->_pos[0]));

    uniform_id = glGetUniformLocation(program.getId(), "CAMERA_LOOK_AT");
    glUniform3fv(uniform_id, 1, &(this->_look_at[0]));

    uniform_id = glGetUniformLocation(program.getId(), "CAMERA_HEAD_UP");
    glUniform3fv(uniform_id, 1, &(this->_head_up[0]));

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
    /* projection (+ window(width, height)) */
    float     fov_deg = 45.0f;
    float     fov_rad = fov_deg * static_cast<float>(M_PI) / 180.0f;
    float     near_clipping_plane = 0.1f;
    float     far_clipping_plane = 100.0f;

    return new Camera(camera_pos,
                      camera_look_at,
                      camera_head_up,
                      fov_rad,
                      near_clipping_plane,
                      far_clipping_plane);
}
