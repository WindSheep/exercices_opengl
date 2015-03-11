#ifndef  TEXTURE_CLASS_HPP
# define TEXTURE_CLASS_HPP

# include "openGL.hpp"
# include <string>

class ShaderProgram;

class Texture
{
public:
  //-/* CONSTRUCTORS / DESTRUCTORS */-//
  /* CONSTRUCTOR */                      Texture(const std::string& path, ShaderProgram& program);
  virtual
  /* DESTRUCTOR */                       ~Texture(void);

  //-/* FUCK CANONICAL MAYBE ? CALL ME MAYBE ? */-//
  /* CONSTRUCTOR */                      Texture(void) = delete;
  /* CONSTRUCTOR */                      Texture(const Texture& src) = delete;
  Texture&                               operator=(const Texture& src) = delete;

  //-/* FUNCTIONS */-//

  //-/* GETTERS / SETTERS */-//
  GLuint                                 getImageId(void) const;
  void                                   getImageId(GLuint& id) const;

  GLuint                                 getId(void) const;
  void                                   getId(GLuint id) const;

private:
  //-/* VARIABLES */-//
  GLuint                                 _image_id;
  GLuint                                 _texture_id;
};

#endif
