#include "Selector2D.class.hpp"
#include "Button2D.class.hpp"
#include "Text2D.class.hpp"
#include <cstdarg>

//-/* CONSTRUCTORS / DESTRUCTORS */-//
/* CONSTRUCTOR */                      Selector2D::Selector2D(unsigned int n, ...) :
  _button_list(), _value(0)
{
  va_list ap;

  va_start(ap, n);
  while (n > 0) {
    Button2D* button = va_arg(ap, Button2D*);

    if (button != NULL) {
      this->_button_list.push_back(button);
    }
    --(n);
  }
  if (this->_button_list.size() >= 1) {
    this->_button_list[this->_value]->setHighlight(true);
  }
  va_end(ap);
}

/* DESTRUCTOR */                       Selector2D::~Selector2D(void)
{
  for (auto it = this->_button_list.begin(), ite = this->_button_list.end(); it != ite; ++(it)) {
    delete *(it);
  }
}

//-/* FUNCTIONS */-//
void                                   Selector2D::draw(void)
{
  for (auto it = this->_button_list.begin(), ite = this->_button_list.end(); it != ite; ++(it)) {
    (*(it))->draw();
  }
}

void                                   Selector2D::previous(void)
{
  if (this->_button_list.size() >= 1) {
    this->_button_list[this->_value]->setHighlight(false);
    --(this->_value);
    while (this->_value < 0) {
      this->_value += this->_button_list.size();
    }
    this->_button_list[this->_value]->setHighlight(true);
  }
}

void                                   Selector2D::next(void)
{
  if (this->_button_list.size() >= 1) {
    this->_button_list[this->_value]->setHighlight(false);
    ++(this->_value);
    while (this->_value >= this->_button_list.size()) {
      this->_value -= this->_button_list.size();
    }
    this->_button_list[this->_value]->setHighlight(true);
  }
}

//-/* GETTERS / SETTERS */-//
unsigned int                           Selector2D::getValue(void) const
{ return this->_value; }

void                                   Selector2D::getValue(unsigned int& value) const
{ value = this->_value; }

const Selector2D::button_holder&       Selector2D::getButtonList(void) const
{ return this->_button_list; }

Selector2D*                            newDefaultSelector2D(void)
{
  return new Selector2D(2,
                        new Button2D(new Text2D("play", 100, 400, 25 + 10)),
                        new Button2D(new Text2D("quit", 200, 400, 25))
                        );
}
