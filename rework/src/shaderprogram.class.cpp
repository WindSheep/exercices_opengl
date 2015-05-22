#include "shaderprogram.class.hpp"

GLuint loadShaders(const std::string& vertex_path,
                   const std::string& fragment_path);

/* CTOR */ ShaderProgram::ShaderProgram(const std::string& vertex_path,
                                        const std::string& fragment_path) :
    _id(loadShaders(vertex_path, fragment_path)) {
}

/* DTOR */ ShaderProgram::~ShaderProgram(void) {
    glDeleteProgram(this->_id);
}

void ShaderProgram::use(void) {
    glUseProgram(this->_id);
}

/* GETTERS && SETTERS {{{ */
GLuint ShaderProgram::getId(void) const {
    return this->_id;
}

void ShaderProgram::getId(GLuint& id) const {
    id = this->_id;
}
/* GETTERS && SETTERS }}} */
