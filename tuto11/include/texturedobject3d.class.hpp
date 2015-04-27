#ifndef  TEXTUREDOBJECT3D_CLASS_HPP
# define TEXTUREDOBJECT3D_CLASS_HPP

# include "opengl.hpp"
# include "object3d.class.hpp"
# include "texture.class.hpp"
# include "shaderprogram.class.hpp"

class Object3D;
class ShaderProgram;
class Texture;

class TexturedObject3D : virtual public Object3D {
public:
    /* CTOR */         TexturedObject3D(const glm::vec3& pos,
                                        const unsigned int n_tri,
                                        const GLfloat* vbuff_data,
                                        const GLfloat* uvbuffer_data,
                                        Texture& texture);
    virtual /* DTOR */ ~TexturedObject3D(void);

    /* DELETED {{{ */
    /* CTOR */         TexturedObject3D(void) = delete;
    /* CTOR */         TexturedObject3D(const TexturedObject3D& src) = delete;
    TexturedObject3D&  operator=(const TexturedObject3D& src) = delete;
    /* DELETED }}} */

    virtual void  draw(void);

    static bool   s_init(void);
    static void   s_deInit(void);
    static bool   s_isInit(void);

protected:
    void          drawPart(void);

private:
    GLuint                _uvbuffer;
    Texture&              _texture;

    static ShaderProgram* s_program;

    friend Object3D* newTexturedTriangle(const glm::vec3& pos);
    friend Object3D* newTexturedCube(const glm::vec3& pos);
};

Object3D* newTexturedTriangle(const glm::vec3& pos);
Object3D* newTexturedCube(const glm::vec3& pos);

#endif
