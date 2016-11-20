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

void Ant::turn(Color color) {
    switch(ANT_RULES[(int) color].rotation) {
        case Move::GO_FRONT:
            break;

        case Move::GO_BACK:
            switch(this->getOrientation()) {
                case Orientation::FRONT:
                    this->setOrientation(BACK);
                    break;
                case Orientation::BACK:
                    this->setOrientation(FRONT);
                    break;
                case Orientation::RIGHT:
                    this->setOrientation(LEFT);
                    break;
                case Orientation::LEFT:
                    this->setOrientation(RIGHT);
                    break;
                case Orientation::UP:
                    this->setOrientation(DOWN);
                    break;
                case Orientation::DOWN:
                    this->setOrientation(UP);
                    break;
            }
            break;

        case Move::GO_RIGHT:
            switch(this->getOrientation()) {
                case Orientation::FRONT:
                    this->setOrientation(RIGHT);
                    break;
                case Orientation::BACK:
                    this->setOrientation(DOWN);
                    break;
                case Orientation::RIGHT:
                    this->setOrientation(UP);
                    break;
                case Orientation::LEFT:
                    this->setOrientation(BACK);
                    break;
                case Orientation::UP:
                    this->setOrientation(FRONT);
                    break;
                case Orientation::DOWN:
                    this->setOrientation(LEFT);
                    break;
            }
            break;

        case Move::GO_LEFT:
            switch(this->getOrientation()) {
                case Orientation::FRONT:
                    this->setOrientation(LEFT);
                    break;
                case Orientation::BACK:
                    this->setOrientation(DOWN);
                    break;
                case Orientation::RIGHT:
                    this->setOrientation(BACK);
                    break;
                case Orientation::LEFT:
                    this->setOrientation(UP);
                    break;
                case Orientation::UP:
                    this->setOrientation(FRONT);
                    break;
                case Orientation::DOWN:
                    this->setOrientation(RIGHT);
                    break;
            }
            break;

        case Move::GO_UP:
            switch(this->getOrientation()) {
                case Orientation::FRONT:
                    this->setOrientation(UP);
                    break;
                case Orientation::BACK:
                    this->setOrientation(DOWN);
                    break;
                case Orientation::RIGHT:
                    this->setOrientation(FRONT);
                    break;
                case Orientation::LEFT:
                    this->setOrientation(BACK);
                    break;
                case Orientation::UP:
                    this->setOrientation(RIGHT);
                    break;
                case Orientation::DOWN:
                    this->setOrientation(LEFT);
                    break;
            }
            break;

        case Move::GO_DOWN:
            switch(this->getOrientation()) {
                case Orientation::FRONT:
                    this->setOrientation(DOWN);
                    break;
                case Orientation::BACK:
                    this->setOrientation(LEFT);
                    break;
                case Orientation::RIGHT:
                    this->setOrientation(FRONT);
                    break;
                case Orientation::LEFT:
                    this->setOrientation(UP);
                    break;
                case Orientation::UP:
                    this->setOrientation(BACK);
                    break;
                case Orientation::DOWN:
                    this->setOrientation(RIGHT);
                    break;
            }
            break;
    }
}


void Ant::move(int incrementing) {
    switch(getOrientation()) {
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
    //turn(color);
    move(ANT_RULES[(int)color].incrementing);
}