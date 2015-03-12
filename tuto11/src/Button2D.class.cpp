#include "Button2D.class.hpp"
#include "Text2D.class.hpp"

//-/* CONSTRUCTORS / DESTRUCTORS */-//
/* CONSTRUCTOR */                      Button2D::Button2D(Text2D* text) :
  _text(text)
{ }

/* DESTRUCTOR */                       Button2D::~Button2D(void)
{ delete this->_text; }

//-/* FUNCTIONS */-//
void                                   Button2D::draw(void)
{ this->_text->draw(); }

//-/* GETTERS / SETTERS */-//
void                                   Button2D::setHighlight(bool highlight)
{ this->_text->setHighlight(highlight); }

bool                                   Button2D::getHighlight(void) const
{ return this->_text->getHighlight(); }

void                                   Button2D::getHighlight(bool& highlight) const
{ this->_text->getHighlight(highlight); }
