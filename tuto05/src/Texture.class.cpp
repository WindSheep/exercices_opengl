#include "Texture.class.hpp"
#include "ShaderProgram.class.hpp"

GLuint                                 loadBMP(const std::string& path);
GLuint                                 loadTGA(const std::string& path);
GLuint                                 loadDDS(const std::string& path);

//-/* CONSTRUCTORS / DESTRUCTORS */-//
/* CONSTRUCTOR */                      Texture::Texture(const std::string& path, ShaderProgram& program) :
  image_id(0), texture_id(0)
{
  this->image_id = 0;
  {
    size_t pos = path.rfind(".");

    if (pos != std::string::npos) {
      const std::string ext = path.substr(pos + 1);
      if (ext == "DDS") {
        this->image_id = loadDDS(path);
      }
      else if (ext == "bmp") {
        this->image_id = loadBMP(path);
      }
    }
  }
  this->texture_id = glGetUniformLocation(program.id, "myTextureSampler");
}

/* DESTRUCTOR */                       Texture::~Texture(void)
{
  glDeleteTextures(1, &(this->image_id));
  glDeleteTextures(1, &(this->image_id));
  glDeleteTextures(1, &(this->texture_id));
}

//-/* FUNCTIONS */-//

//-/* GETTERS / SETTERS */-//

//-/* VARIABLES */-//
