//
// Created by benji on 26/11/16.
//

#include "Rules.h"

Rules::Rules(RuleDefinition rule) {
    loadRule(rule);
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

void Rules::loadRule(RuleDefinition ruleDefinition) {
    reset();

    for(int i = 0 ; i < ruleDefinition.size() ; i++) {
        add(ruleDefinition.color(i), ruleDefinition.move(i));
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