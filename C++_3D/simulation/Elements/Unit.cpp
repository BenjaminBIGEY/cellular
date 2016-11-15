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

glm::vec4 Unit::getColor(Color color, float alpha) {
    switch(color) {
        case Color::WHITE: return glm::vec4(1, 1, 1, alpha);
        case Color::BLACK: return glm::vec4(0, 0, 0, alpha);
        case Color::GREEN: return glm::vec4(0, 1, 0, alpha);
        case Color::RED: return glm::vec4(1, 0, 0, alpha);
        case Color::BLUE: return glm::vec4(0, 0, 1, alpha);
        case Color::YELLOW: return glm::vec4(1, 1, 0, alpha);
        case Color::ORANGE: return glm::vec4(1, 165/255, 0, alpha);
        //case Color::MAGENTA: return glm::vec4(1, 0, 1, alpha);
        default: return glm::vec4(0, 0, 0, alpha); // black unit
    }
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