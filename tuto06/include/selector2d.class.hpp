#ifndef  SELECTOR2D_CLASS_HPP
# define SELECTOR2D_CLASS_HPP

# include "opengl.hpp"
# include <vector>

class Button2D;

class Selector2D {
public:
    typedef std::vector<Button2D*> button_holder;

    /* CTOR */         Selector2D(unsigned int n, ...);
    virtual /* DTOR */ ~Selector2D(void);

    /* DELETED {{{ */
    /* CONSTRUCTOR */  Selector2D(void) = delete;
    /* CONSTRUCTOR */  Selector2D(const Selector2D& src) = delete;
    Selector2D&        operator=(const Selector2D& src) = delete;
    /* DELETED }}} */

    void               draw(void);
    void               previous(void);
    void               next(void);

    /* GETTERS && SETTERS {{{ */
    unsigned int         getValue(void) const;
    void                 getValue(unsigned int& value) const;

    const button_holder& getButtonList(void) const;
    /* GETTERS && SETTERS }}} */

private:
    button_holder _button_list;
    int           _value;
};

Selector2D* newDefaultSelector2D(void);

#endif
