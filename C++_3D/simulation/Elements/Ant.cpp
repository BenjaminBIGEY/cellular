//
// Created by benji on 24/10/16.
//

#include "Ant.h"

Ant::Ant(glm::vec3 position, Orientation orientation) : _position(position) {
    _orientation = orientation;
}

glm::vec3 Ant::getPosition() {
    return _position;
}

Orientation Ant::getOrientation() {
    return _orientation;
}

// TODO
void Ant::turn(Color color) {
    /*switch(ANT_RULES[(int)color].rotation) {
        case Move::GO_FRONT:

    }*/
}

void Ant::move(int incrementing) {
    switch (getOrientation()) {
        case FRONT:
            _position.y+=incrementing;
            break;
        case RIGHT:
            _position.x+=incrementing;
            break;
        case BACK:
            _position.y-=incrementing;
            break;
        case LEFT:
            _position.x-=incrementing;
            break;
        case UP:
            _position.z+=incrementing;
            break;
        case DOWN:
            _position.z-=incrementing;
            break;
    }
}

void Ant::update(Color color) {
    turn(color);
    move(ANT_RULES[(int)color].incrementing);
}