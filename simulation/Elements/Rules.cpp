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
    else
        std::cerr << "Warning : the color '" << color.getColorName() << "' already exists." << std::endl;
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
    Move move = getRule(cubeColor);
    if(move == Move::DO_NOTHING)
        return currentOrientation;
    return ORIENTATION_CHANGES[(int)move][(int)currentOrientation];
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
    if(color == NULL_COLOR)
        return NULL_COLOR;

    for(int i = 0 ; i < _listRules.size() - 1 ; i++) {
        if(color == _listRules[i].first)
            return _listRules[i+1].first;
    }
    return Color(_listRules[0].first);
}

std::string Rules::getRules() {
    std::string rules;
    std::string color;
    int sizeMax = 0;
    for(int i = 0 ; i < _listRules.size() ; i++) {
        if(_listRules[i].first.getColorName().size() > sizeMax)
            sizeMax = (int)_listRules[i].first.getColorName().size();
    }

    for(int i = 0 ; i < _listRules.size() ; i++) {
        color = _listRules[i].first.getColorName();
        rules += color;
        for(int k = 0 ; k < sizeMax - color.size() ; k++)
            rules += ' ';
        rules += " : " + getMoveName(_listRules[i].second) + "\n";
    }

    return rules;
}

std::string Rules::getMoveName(Move move) {
    switch(move) {
        case Move::GO_FRONT: return "GO_front";
        case Move::GO_BACK: return "GO_back";
        case Move::GO_RIGHT: return "GO_right";
        case Move::GO_LEFT: return "GO_left";
        case Move::GO_UP: return "GO_up";
        case Move::GO_DOWN: return "GO_down";
        case Move::DO_NOTHING: return "do nothing";
    }
}