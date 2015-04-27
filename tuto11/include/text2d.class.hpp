#ifndef  TEXT2D_CLASS_HPP
# define TEXT2D_CLASS_HPP

# include "opengl.hpp"
# include <string>

class ShaderProgram;
class Texture;

class Text2D {
public:
  /* CTOR */         Text2D(const std::string& str,
                            unsigned int y, unsigned int x,
                            unsigned int size, bool highlight = false);
  virtual /* DTOR */ ~Text2D(void);

    /* DELETED {{{ */
    /* CONSTRUCTOR */ Text2D(void) = delete;
    /* CONSTRUCTOR */ Text2D(const Text2D& src) = delete;
    Text2D&           operator=(const Text2D& src) = delete;
    /* DELETED }}} */

    virtual void      draw(void);

    static bool       s_init(void);
    static void       s_deInit(void);
    static bool       s_isInit(void);

    /* GETTERS && SETTERS {{{ */
    void              setHighlight(bool highlight);

    bool              getHighlight(void) const;
    void              getHighlight(bool& highlight) const;
    /* GETTERS && SETTERS }}} */

private:
    void              drawPart(void);

    unsigned int          _n_tri;
    GLuint                _vbuffer;
    GLuint                _uvbuffer;
    bool                  _highlight;
    ShaderProgram*        _program;
    const std::string     _str;
    const Texture*        _font;

    static ShaderProgram* s_program;
    static Texture*       s_texture_normal;
    static Texture*       s_texture_highlight;
};

#endif
