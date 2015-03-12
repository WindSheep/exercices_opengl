#ifndef  TEXT2D_CLASS_HPP
# define TEXT2D_CLASS_HPP

# include "openGL.hpp"
# include <string>

class ShaderProgram;
class Texture;

class Text2D
{
public:
  //-/* CONSTRUCTORS / DESTRUCTORS */-//
  /* CONSTRUCTOR */                      Text2D(const std::string& str, unsigned int y, unsigned int x, unsigned int size, bool highlight = false);
  virtual
  /* DESTRUCTOR */                       ~Text2D(void);

  //-/* FUCK CANONICAL MAYBE ? CALL ME MAYBE ? */-//
  /* CONSTRUCTOR */                      Text2D(void) = delete;
  /* CONSTRUCTOR */                      Text2D(const Text2D& src) = delete;
  Text2D&                                operator=(const Text2D& src) = delete;

  //-/* FUNCTIONS */-//
  virtual
  void                                   draw(void);

  static
  bool                                   s_init(void);

  static
  void                                   s_deInit(void);

  static
  bool                                   s_isInit(void);

  //-/* GETTERS / SETTERS */-//
  void                                   setHighlight(bool highlight);

  bool                                   getHighlight(void) const;
  void                                   getHighlight(bool& highlight) const;

private:
  //-/* FUNCTIONS */-//
  void                                   drawPart(void);

  //-/* VARIABLES */-//
  unsigned int                           _n_tri;
  GLuint                                 _vbuffer;
  GLuint                                 _uvbuffer;
  bool                                   _highlight;
  // const std::string                      _str;
  // const Texture*                         _font;

  static
  ShaderProgram*                         _program;

  static
  Texture*                               _texture_normal;

  static
  Texture*                               _texture_highlight;
};
/*                                     */

#endif
