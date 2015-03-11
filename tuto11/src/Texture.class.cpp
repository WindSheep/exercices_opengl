#include "Texture.class.hpp"
#include "ShaderProgram.class.hpp"

GLuint                                 loadBMP(const std::string& path);
GLuint                                 loadTGA(const std::string& path);
GLuint                                 loadDDS(const std::string& path);

static GLuint                          _loadTexture(const std::string& path)
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

//-/* CONSTRUCTORS / DESTRUCTORS */-//
/* CONSTRUCTOR */                      Texture::Texture(const std::string& path, ShaderProgram& program) :
  _image_id(_loadTexture(path)), _texture_id(glGetUniformLocation(program.getId(), "myTextureSampler"))
{ }

/* DESTRUCTOR */                       Texture::~Texture(void)
{
  glDeleteTextures(1, &(this->_image_id));
  glDeleteTextures(1, &(this->_texture_id));
}

//-/* FUNCTIONS */-//

//-/* GETTERS / SETTERS */-//
GLuint                                 Texture::getImageId(void) const
{ return this->_image_id; }

void                                   Texture::getImageId(GLuint& id) const
{ id = this->_image_id; }

GLuint                                 Texture::getId(void) const
{ return this->_texture_id; }

void                                   Texture::getId(GLuint id) const
{ id = this->_texture_id; }
