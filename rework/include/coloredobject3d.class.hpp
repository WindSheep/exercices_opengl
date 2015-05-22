#ifndef  COLOREDOBJECT3D_CLASS_HPP
# define COLOREDOBJECT3D_CLASS_HPP

# include "opengl.hpp"
# include "object3d.class.hpp"
# include "shaderprogram.class.hpp"

class Object3D;
class ShaderProgram;

class ColoredObject3D : virtual public Object3D {
public:
    /* CTOR */         ColoredObject3D(const glm::vec3& pos,
                                       const unsigned int n_tri,
                                       const GLfloat* vbuff_data,
                                       const GLfloat* cbuffer_data);
    virtual /* DTOR */ ~ColoredObject3D(void);

    /* DELETED {{{ */
    /* CONSTRUCTOR */  ColoredObject3D(void) = delete;
    /* CONSTRUCTOR */  ColoredObject3D(const ColoredObject3D& src) = delete;
    ColoredObject3D&   operator=(const ColoredObject3D& src) = delete;
    /* DELETED }}} */

    virtual void draw(void);

    static bool  s_init(void);
    static void  s_deInit(void);
    static bool  s_isInit(void);

protected:
    void        drawPart(void);

private:
    GLuint                _cbuffer;
    static ShaderProgram* s_program;
};

Object3D* newColoredTriangle(const glm::vec3& pos);
Object3D* newColoredCube(const glm::vec3& pos);

#endif
