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

glm::vec3 Unit::getColor(Color color) {
    switch(color) {
        case Color::WHITE: return glm::vec3(1.0, 1.0, 1.0);
        case Color::RED: return glm::vec3(1, 0, 0);
        /*case Color::GREEN: return glm::vec3(0, 1, 0);
        case Color::RED: return glm::vec3(1, 0, 0);
        case Color::BLUE: return glm::vec3(0, 0, 1);
        case Color::YELLOW: return glm::vec3(1, 1, 0);
        case Color::ORANGE: return glm::vec3(1, 165.0f/255, 0);*/
        //case Color::MAGENTA: return glm::vec4(1, 0, 1, alpha);
        default: return glm::vec3(0, 0, 0); // black unit
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