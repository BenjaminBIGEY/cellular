//
// Created by benji on 26/11/16.
//

#include "Color.h"

Color::Color(AllColors c) {
    setColor(c);
}

Color::Color(std::string color) {
    setColor(color);
}

AllColors Color::getColor() {
    return _color;
}

glm::vec3 Color::getColorGraphic() {
    switch(_color) {
        case AllColors::WHITE: return glm::vec3(1, 1, 1);
        case AllColors::RED: return glm::vec3(1, 0, 0);
        case AllColors::GREEN: return glm::vec3(0, 1, 0);
        case AllColors::BLACK: return glm::vec3(0, 0, 0);
        case AllColors::BLUE: return glm::vec3(0, 0, 1);
        case AllColors::YELLOW: return glm::vec3(1, 1, 0);
        case AllColors::ORANGE: return glm::vec3(1, 165.0f/255, 0);
        case AllColors::MAGENTA: return glm::vec3(1, 0, 1);
        default: return glm::vec3(0, 0, 0); // black unit
    }
}

std::string Color::getColorName() {
    switch(_color) {
        case AllColors ::BLACK:
            return "black";
        case AllColors::BLUE:
            return "blue";
        case AllColors::GREEN:
            return "green";
        case AllColors::MAGENTA:
            return "magenta";
        case AllColors::ORANGE:
            return "orange";
        case AllColors::RED:
            return "red";
        case AllColors::WHITE:
            return "white";
        case AllColors::YELLOW:
            return "yellow";
        case AllColors::NULL_COLOR:
            std::cerr << "Warning : NULL_COLOR" << std::endl;
            return "null";
    }
}


void Color::setColor(AllColors c) {
    _color = c;
}

bool Color::setColor(std::string color) {
    if(color == "black")   _color = AllColors::BLACK;
    else if(color == "blue")    _color = AllColors::BLUE;
    else if(color == "green")   _color = AllColors::GREEN;
    else if(color == "magenta") _color = AllColors::MAGENTA;
    else if(color == "orange")  _color = AllColors::ORANGE;
    else if(color == "red")     _color = AllColors::RED;
    else if(color == "white")   _color = AllColors::WHITE;
    else if(color == "yellow")  _color = AllColors::YELLOW;
    else {std::cerr << "Unexisting color : '" << color << "'" << std::endl;return false;}
    return true;
}

bool Color::exists() {
    return _color != NULL_COLOR;
}

bool Color::equal(const Color &other) const {
    return this->_color == other._color;
}

bool Color::less(const Color &other) const {
    return (int)this->_color < (int)other._color;
}