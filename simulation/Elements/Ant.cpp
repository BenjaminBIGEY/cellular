//
// Created by benji on 24/10/16.
//

#include "Ant.h"

Ant::Ant(Vector3 position, Orientation orientation) : _position(position) {
    _orientation = orientation;
}

Vector3 Ant::getPosition() {
    return _position;
}

Orientation Ant::getOrientation() {
    return _orientation;
}

void Ant::setOrientation(Orientation orientation) {
    _orientation = orientation;
}


void Ant::move(int incrementing) {
    switch(getOrientation()) {
        case FRONT:
            _position.x+=incrementing;
            break;
        case RIGHT:
            _position.y+=incrementing;
            break;
        case BACK:
            _position.x-=incrementing;
            break;
        case LEFT:
            _position.y-=incrementing;
            break;
        case UP:
            _position.z+=incrementing;
            break;
        case DOWN:
            _position.z-=incrementing;
            break;
    }
}

void Ant::update(Color color, std::shared_ptr<Rules> rules) {
    this->setOrientation(rules->getNewOrientation(_orientation, color));
    move(1);
}