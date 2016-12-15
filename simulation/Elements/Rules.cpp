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