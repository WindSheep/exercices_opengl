#include "button2d.class.hpp"
#include "text2d.class.hpp"

/* CTOR */ Button2D::Button2D(Text2D* text) :
    _text(text) {
}

/* DTOR */ Button2D::~Button2D(void) {
    delete this->_text;
}

void Button2D::draw(void) {
    this->_text->draw();
}

/* GETTERS && SETTERS {{{ */
void Button2D::setHighlight(bool highlight) {
    this->_text->setHighlight(highlight);
}

bool Button2D::getHighlight(void) const {
    return this->_text->getHighlight();
}

void Button2D::getHighlight(bool& highlight) const {
    this->_text->getHighlight(highlight);
}
/* GETTERS && SETTERS }}} */
