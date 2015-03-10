#ifndef  TEXTURE_CLASS_HPP
# define TEXTURE_CLASS_HPP

# include "openGL.hpp"
# include <string>

class ShaderProgram;

class Texture
{
public:
  friend class                           Object3D;
  // enum eType : unsigned int
  // {
  //   _MIN   = 0,
  //   BMP    = 0,
  //   _MAX   = 0,
  //   _LIMIT = 1,
  // };

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

  //-/* VARIABLES */-//
  GLuint                                 image_id;
  GLuint                                 texture_id;
};

#endif
