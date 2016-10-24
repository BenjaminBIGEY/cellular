//
// Created by benji on 24/10/16.
//

#include "Ant.h"

Ant::Ant(int x, int y, int z, Orientation orientation) : _pos{x, y, z} {
    _orientation = orientation;
}

Vector3 Ant::getPosition() {
    return _pos;
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
            _pos.y+=incrementing;
            break;
        case RIGHT:
            _pos.x+=incrementing;
            break;
        case BACK:
            _pos.y-=incrementing;
            break;
        case LEFT:
            _pos.x-=incrementing;
            break;
        case UP:
            _pos.z+=incrementing;
            break;
        case DOWN:
            _pos.z-=incrementing;
            break;
    }
}

void Ant::update(Color color) {
    turn(color);
    move(ANT_RULES[(int)color].incrementing);
}