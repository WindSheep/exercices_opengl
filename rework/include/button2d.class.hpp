#ifndef  BUTTON2D_CLASS_HPP
# define BUTTON2D_CLASS_HPP

# include "opengl.hpp"

class Text2D;

class Button2D {
public:
    /* CTOR */         Button2D(Text2D* text);
    virtual /* DTOR */ ~Button2D(void);

    /* DELETED {{{ */
    /* CTOR */         Button2D(void) = delete;
    /* CTOR */         Button2D(const Button2D& src) = delete;
    Button2D&          operator=(const Button2D& src) = delete;
    /* DELETED }}} */

    void draw(void);

    /* GETTERS && SETTERS {{{ */
    void setHighlight(bool highlight);
    bool getHighlight(void) const;
    void getHighlight(bool& highlight) const;
    /* GETTERS && SETTERS }}} */

private:
    Text2D*                                _text;
    // Cadre2D*                               _cadre;
};

#endif
