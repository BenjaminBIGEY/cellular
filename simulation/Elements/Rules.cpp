//
// Created by benji on 26/11/16.
//

#include "Rules.h"

Rules::Rules(PreConfiguredRules rules) {
    loadPreConfiguredRule(rules);
}

void Rules::add(std::string color, Move rule) {
    Color c(color);
    add(c, rule);
}

void Rules::add(Color color, Move rule) {
    bool existingColor = false;
    for(int i = 0 ; i < _listRules.size() ; i++) {
        if(color == _listRules[i].first)
            existingColor = true;
    }

    if(!existingColor)
        _listRules.push_back({color, rule});
}

void Rules::reset() {
    _listRules.clear();
}

void Rules::loadPreConfiguredRule(PreConfiguredRules rules) {
    reset();

    switch(rules) {
        case PreConfiguredRules::X_Y_PLANE_2COLORS:
            add(WHITE, GO_RIGHT);
            add(BLACK, GO_LEFT);
            break;
        case PreConfiguredRules::X_Z_PLANE_2COLORS:
            add(WHITE, GO_FRONT);
            add(BLACK, GO_BACK);
            break;
        case PreConfiguredRules::Y_Z_PLANE_2COLORS:
            add(WHITE, GO_UP);
            add(BLACK, GO_DOWN);
            break;

        case PreConfiguredRules::X_Y_Z_8_COLORS:
            add(RED, GO_DOWN);
            add(BLACK, GO_BACK);
            add(BLUE, DO_NOTHING);
            add(MAGENTA, GO_BACK);
            add(WHITE, GO_DOWN);
            add(GREEN, GO_FRONT);
            add(ORANGE, GO_RIGHT);
            add(YELLOW, GO_LEFT);
            break;
        case PreConfiguredRules::STAIRS:
            add(ORANGE, GO_BACK);
            add(WHITE, GO_UP);
            add(BLACK, GO_DOWN);
            break;
        default:
            break;
    }
}

std::vector<Color> Rules::getListColors() {
    std::vector<Color> result;

    for(int i = 0 ; i < _listRules.size() ; i++) {
        result.push_back(_listRules[i].first);
    }
    return result;
}

Orientation Rules::getNewOrientation(Orientation currentOrientation, Color cubeColor) {
    switch(getRule(cubeColor)) {
        case Move::GO_FRONT:
            switch(currentOrientation) {
                case Orientation::FRONT:
                    return DOWN;
                case Orientation::BACK:
                    return UP;
                case Orientation::RIGHT:
                    return FRONT;
                case Orientation::LEFT:
                    return BACK;
                case Orientation::UP:
                    return FRONT;
                case Orientation::DOWN:
                    return BACK;
            }
            break;

        case Move::GO_BACK:
            switch(currentOrientation) {
                case Orientation::FRONT:
                    return UP;
                case Orientation::BACK:
                    return DOWN;
                case Orientation::RIGHT:
                    return BACK;
                case Orientation::LEFT:
                    return FRONT;
                case Orientation::UP:
                    return BACK;
                case Orientation::DOWN:
                    return FRONT;
            }
            break;

        case Move::GO_RIGHT:
            switch(currentOrientation) {
                case Orientation::FRONT:
                    return RIGHT;
                case Orientation::BACK:
                    return LEFT;
                case Orientation::RIGHT:
                    return BACK;
                case Orientation::LEFT:
                    return FRONT;
                case Orientation::UP:
                    return RIGHT;
                case Orientation::DOWN:
                    return LEFT;
            }
            break;

        case Move::GO_LEFT:
            switch(currentOrientation) {
                case Orientation::FRONT:
                    return LEFT;
                case Orientation::BACK:
                    return RIGHT;
                case Orientation::RIGHT:
                    return FRONT;
                case Orientation::LEFT:
                    return BACK;
                case Orientation::UP:
                    return LEFT;
                case Orientation::DOWN:
                    return RIGHT;
            }
            break;

        case Move::GO_UP:
            switch(currentOrientation) {
                case Orientation::FRONT:
                    return UP;
                case Orientation::BACK:
                    return DOWN;
                case Orientation::RIGHT:
                    return UP;
                case Orientation::LEFT:
                    return DOWN;
                case Orientation::UP:
                    return LEFT;
                case Orientation::DOWN:
                    return RIGHT;
            }
            break;

        case Move::GO_DOWN:
            switch(currentOrientation) {
                case Orientation::FRONT:
                    return DOWN;
                case Orientation::BACK:
                    return UP;
                case Orientation::RIGHT:
                    return DOWN;
                case Orientation::LEFT:
                    return UP;
                case Orientation::UP:
                    return RIGHT;
                case Orientation::DOWN:
                    return LEFT;
            }
            break;
        case Move::DO_NOTHING:
            return currentOrientation;
    }
}

Move Rules::getRule(Color color) {
    for(int i = 0 ; i < _listRules.size() ; i++) {
        if(color == _listRules[i].first)
            return _listRules[i].second;
    }
    std::cerr << "Unexisting rule color" << std::endl;
    return DO_NOTHING;
}

Color Rules::nextColor(Color color) {
    std::vector<Color> listColors = getListColors();

    for(int i = 0 ; i < listColors.size() - 1 ; i++) {
        if(color == listColors[i])
            return listColors[i+1];
    }
    return Color((AllColors)0);
}