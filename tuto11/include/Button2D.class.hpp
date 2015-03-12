#ifndef  BUTTON2D_CLASS_HPP
# define BUTTON2D_CLASS_HPP

# include "openGL.hpp"
# include <string>

class ShaderProgram;
class Text2D;
class Texture;

class Button2D
{
public:
  //-/* CONSTRUCTORS / DESTRUCTORS */-//
  /* CONSTRUCTOR */                      Button2D(Text2D* text);
  virtual
  /* DESTRUCTOR */                       ~Button2D(void);

  //-/* FUCK CANONICAL MAYBE ? CALL ME MAYBE ? */-//
  /* CONSTRUCTOR */                      Button2D(void) = delete;
  /* CONSTRUCTOR */                      Button2D(const Button2D& src) = delete;
  Button2D&                                operator=(const Button2D& src) = delete;

  //-/* FUNCTIONS */-//
  void                                   draw(void);

  //-/* GETTERS / SETTERS */-//
  void                                   setHighlight(bool highlight);

  bool                                   getHighlight(void) const;
  void                                   getHighlight(bool& highlight) const;

private:
  //-/* FUNCTIONS */-//

  //-/* VARIABLES */-//
  Text2D*                                _text;
  // Cadre2D*                               _cadre;
};
/*                                     */

#endif
