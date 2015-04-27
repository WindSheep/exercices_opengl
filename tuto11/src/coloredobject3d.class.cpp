#include "coloredobject3d.class.hpp"
#include "camera.class.hpp"

ShaderProgram* ColoredObject3D::s_program = 0;

/* CTOR */ ColoredObject3D::ColoredObject3D(const glm::vec3& pos,
                                            const unsigned int n_tri,
                                            const GLfloat* vbuff_data,
                                            const GLfloat* cbuff_data) :
    Object3D(pos, n_tri, vbuff_data), _cbuffer(0) {
    glGenBuffers(1, &(this->_cbuffer));
    glBindBuffer(GL_ARRAY_BUFFER, this->_cbuffer);
    glBufferData(GL_ARRAY_BUFFER, 9 * this->_n_tri * sizeof(*(cbuff_data)),
                 cbuff_data, GL_STATIC_DRAW);
}

/* DTOR */ ColoredObject3D::~ColoredObject3D(void) {
    glDeleteBuffers(1, &(this->_cbuffer));
}

void ColoredObject3D::drawPart(void) {
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, this->_cbuffer);
    glVertexAttribPointer(
                          1,        // layout
                          3,        // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized
                          0,        // stride
                          (void*)0  // array_buffer offset
                          );
}

void ColoredObject3D::draw(void) {
    if (ColoredObject3D::s_isInit() || ColoredObject3D::s_init()) {
        this->_program = ColoredObject3D::s_program;
        modifyMVP(*(this->_program), *(Camera::s_getCamera()), this->_pos);

        Object3D::drawPart();
        this->drawPart();
        glDrawArrays(GL_TRIANGLES, 0, this->_n_tri * 3);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
    }
}

/* GETTERS && SETTERS {{{ */
bool ColoredObject3D::s_init(void) {
    if (!ColoredObject3D::s_isInit()) {
        const std::string dir = "shaders/coloredobject3d/";

        ColoredObject3D::s_program =
            new ShaderProgram(dir + ShaderProgram::s_getVertexShaderName(),
                              dir + ShaderProgram::s_getFragmentShaderName());
    }
    return true;
}

bool ColoredObject3D::s_isInit(void) {
    return ColoredObject3D::s_program != NULL;
}

void ColoredObject3D::s_deInit(void) {
    delete ColoredObject3D::s_program; ColoredObject3D::s_program = NULL;
}
/* GETTERS && SETTERS }}} */
