#ifndef  SELECTOR2D_CLASS_HPP
# define SELECTOR2D_CLASS_HPP

# include "openGL.hpp"
# include <vector>

class Button2D;

class Selector2D
{
public:
  typedef std::vector<Button2D*>         button_holder;

  //-/* CONSTRUCTORS / DESTRUCTORS */-//
  /* CONSTRUCTOR */                      Selector2D(unsigned int n, ...);
  virtual
  /* DESTRUCTOR */                       ~Selector2D(void);

  //-/* FUCK CANONICAL MAYBE ? CALL ME MAYBE ? */-//
  /* CONSTRUCTOR */                      Selector2D(void) = delete;
  /* CONSTRUCTOR */                      Selector2D(const Selector2D& src) = delete;
  Selector2D&                            operator=(const Selector2D& src) = delete;

  //-/* FUNCTIONS */-//
  void                                   draw(void);
  void                                   previous(void);
  void                                   next(void);

  //-/* GETTERS / SETTERS */-//
  unsigned int                           getValue(void) const;
  void                                   getValue(unsigned int& value) const;

  const button_holder&                   getButtonList(void) const;

private:
  //-/* VARIABLES */-//
  button_holder                          _button_list;
  int                                    _value;
};
/*                                     */
Selector2D*                            newDefaultSelector2D(void);

#endif
