#ifndef  CAMERA_CLASS_HPP
# define CAMERA_CLASS_HPP

# include "opengl.hpp"

class Camera {
public:
    /* CTOR */         Camera(const glm::mat4& view, const glm::mat4& projection);
    virtual /* DTOR */ ~Camera(void);

    /* DELETED {{{ */
    /* CTOR */         Camera(void) = delete;
    /* CTOR */         Camera(const Camera& src) = delete;
    Camera&            operator=(const Camera& src) = delete;
    /* DELETED }}} */

    /* GETTERS && SETTERS {{{ */
    const glm::mat4& getView(void) const;
    const glm::mat4& getProjection(void) const;

    static void      s_setCamera(Camera* camera);
    static Camera*   s_getCamera(void);
    /* GETTERS && SETTERS }}} */

protected:
    glm::mat4 _view;
    glm::mat4 _projection;

private:
    static Camera* _camera;
};

Camera* newCamera(void);

#endif
