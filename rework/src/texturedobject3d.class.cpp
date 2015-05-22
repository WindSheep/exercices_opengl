#include "texturedobject3d.class.hpp"
#include "camera.class.hpp"

ShaderProgram* TexturedObject3D::s_program = 0;

/* CTOR */ TexturedObject3D::TexturedObject3D(const glm::vec3& pos,
                                              const unsigned int n_tri,
                                              const GLfloat* vbuff_data,
                                              const GLfloat* uvbuff_data,
                                              Texture& texture) :
    Object3D(pos, n_tri, vbuff_data), _uvbuffer(0), _texture(texture) {
    glGenBuffers(1, &(this->_uvbuffer));
    glBindBuffer(GL_ARRAY_BUFFER, this->_uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, 9 * this->_n_tri * sizeof(*(uvbuff_data)), uvbuff_data, GL_STATIC_DRAW);
}

/* DTOR */ TexturedObject3D::~TexturedObject3D(void) {
    glDeleteBuffers(1, &(this->_uvbuffer));
}

void TexturedObject3D::drawPart(void) {
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, this->_uvbuffer);
    glVertexAttribPointer(
                          1,        // layout
                          2,        // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized
                          0,        // stride
                          (void*)0  // array buffer offset
                          );

    this->_texture.load(*(this->_program));
}

void TexturedObject3D::draw(void) {
    if (TexturedObject3D::s_isInit() || TexturedObject3D::s_init()) {
        this->_program = TexturedObject3D::s_program;
		this->_program->use();
		Camera::s_getCamera()->modifyMVP(*(this->_program),
                                         this->_pos);

        Object3D::drawPart();
        this->drawPart();
        glDrawArrays(GL_TRIANGLES, 0, this->_n_tri * 3);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);
    }
}

/* GETTERS && SETTERS {{{ */
bool TexturedObject3D::s_init(void) {
    if (!TexturedObject3D::s_isInit()) {
        const std::string name = "shaders/texturedobject3d";

        TexturedObject3D::s_program =
            new ShaderProgram(name + ".vert",
                              name + ".frag");
    }
    return true;
}

bool TexturedObject3D::s_isInit(void) {
    return TexturedObject3D::s_program != NULL;
}

void TexturedObject3D::s_deInit(void) {
    delete TexturedObject3D::s_program; TexturedObject3D::s_program = NULL;
}
/* GETTERS && SETTERS }}} */
