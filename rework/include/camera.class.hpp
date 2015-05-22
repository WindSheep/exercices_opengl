#ifndef  CAMERA_CLASS_HPP
# define CAMERA_CLASS_HPP

# include "opengl.hpp"
# include "shaderprogram.class.hpp"

class ShaderProgram;

class Camera {
public:
    /* CTOR */         Camera(const glm::vec3& camera_pos,
                              const glm::vec3& camera_look_at,
                              const glm::vec3& camera_head_up,
                              float fov_rad,
                              float near_clipping_plane,
                              float far_clipping_plane);
    virtual /* DTOR */ ~Camera(void);

    /* DELETED {{{ */
    /* CTOR */         Camera(void) = delete;
    /* CTOR */         Camera(const Camera& src) = delete;
    Camera&            operator=(const Camera& src) = delete;
    /* DELETED }}} */

    void               modifyMVP(ShaderProgram& program, const glm::vec3& pos);

    /* GETTERS && SETTERS {{{ */
    static void      s_setCamera(Camera* camera);
    static Camera*   s_getCamera(void);
    /* GETTERS && SETTERS }}} */

protected:
    glm::vec3 _pos;
    glm::vec3 _look_at;
    glm::vec3 _head_up;

    float     _fov_rad;
    float     _near_clipping_plane;
    float     _far_clipping_plane;

private:
    static Camera* _camera;
};

Camera* newCamera(void);

#endif
