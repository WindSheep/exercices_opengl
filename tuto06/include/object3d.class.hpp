#ifndef  OBJECT3D_CLASS_HPP
# define OBJECT3D_CLASS_HPP

# include "opengl.hpp"
# include "shaderprogram.class.hpp"

class Camera;
class ShaderProgram;

class Object3D {
public:
    /* CTOR */         Object3D(const glm::vec3& pos,
                                const unsigned int n_tri,
                                const GLfloat* vbuff_data);
    virtual /* DTOR */ ~Object3D(void);

    /* DELETED {{{ */
    /* CTOR */         Object3D(void) = delete;
    /* CTOR */         Object3D(const Object3D& src) = delete;
    Object3D&          operator=(const Object3D& src) = delete;
    /* DELETED }}} */

    static bool s_init(void);
    static void s_deInit(void);
    static bool s_isInit(void);

    virtual void draw(void);

protected:
    void        drawPart(void);

    glm::vec3             _pos;
    const unsigned int    _n_tri;
    ShaderProgram*        _program;

private:
    GLuint                _vbuffer;

    static ShaderProgram* s_program;
};

Object3D* newTriangle(const glm::vec3& pos);
Object3D* newCube(const glm::vec3& pos);
void modifyMVP(ShaderProgram& program, const Camera& camera, const glm::vec3& pos);

#endif
