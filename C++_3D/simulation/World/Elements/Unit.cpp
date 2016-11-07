//
// Created by benji on 24/10/16.
//

#include "Unit.h"

Unit::Unit(Color c) {
    _color = c;
}

Color Unit::getColor() {
    return _color;
}

void Unit::setColor(Color c) {
    _color = c;
}

Color Unit::operator++(int) {
    Color next_color = (Color)((int)this->getColor() + 1);

    if (next_color == Color::NBR) {
        this->setColor((Color) 0);
        return (Color) 0;
    } else {
        this->setColor(next_color);
        return next_color;
    }
}