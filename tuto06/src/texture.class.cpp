#include "texture.class.hpp"
#include "shaderprogram.class.hpp"

GLuint loadBMP(const std::string& path);
GLuint loadTGA(const std::string& path);
GLuint loadDDS(const std::string& path);

static GLuint _loadTexture(const std::string& path)
{
  GLuint id = 0;
  size_t pos = path.rfind(".");

  if (pos != std::string::npos) {
    const std::string ext = path.substr(pos + 1);
    if (ext == "DDS") {
      id = loadDDS(path);
    }
    else if (ext == "bmp") {
      id = loadBMP(path);
    }
  }
  return id;
}

/* CTOR */ Texture::Texture(const std::string& path) :
    _id(_loadTexture(path)) {
}

/* DTOR */ Texture::~Texture(void) {
    glDeleteTextures(1, &(this->_id));
}

void Texture::load(const ShaderProgram& program) const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->_id);
    glUniform1i(glGetUniformLocation(program.getId(), "textureSampler"), 0);
}

/* GETTERS / SETTERS {{{ */
GLuint Texture::getId(void) const {
    return this->_id;
}

void Texture::getId(GLuint& id) const {
    id = this->_id;
}
/* GETTERS / SETTERS }}} */
