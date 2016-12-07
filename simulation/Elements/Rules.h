//
// Created by benji on 26/11/16.
//

#ifndef LANGTON3D_RULES_H
#define LANGTON3D_RULES_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Color.h"

#define PRE_CONFIGURED_RULES_NUMBER 10

// Orientation of the ant at the instant t
enum Orientation {
    FRONT = 0,  // +X
    BACK,       // -X
    RIGHT,      // +Y
    LEFT,       // -Y
    UP,         // +Z
    DOWN        // -Z
};

// Rule of each color : ant turn at left or right after the colored square?
enum Move {
    GO_FRONT = 1,
    GO_BACK,
    GO_RIGHT,
    GO_LEFT,
    GO_UP,
    GO_DOWN,
    DO_NOTHING
};

struct RuleDefinition {
    RuleDefinition(){}
    RuleDefinition(std::vector<std::pair<Color, Move>> rules) : _list(rules) {}

    void addRule(Color color, Move move) {
        std::pair<Color, Move> pair(color, move);
        _list.push_back(pair);
    }

    int size() {return (int)_list.size();}
    Color color(int id) {return _list[id].first;}
    Move move(int id) {return _list[id].second;}

private:
    std::vector<std::pair<Color, Move>> _list;
};

const RuleDefinition preConfiguredRules[PRE_CONFIGURED_RULES_NUMBER] = {
        // (X, Y) plane with 2 colors
        {{{WHITE, GO_RIGHT},
          {BLACK, GO_LEFT}}},

        // (X, Z) plane with 2 colors
        {{{WHITE, GO_FRONT},
          {BLACK, GO_BACK}}},

        // (Y, Z) place with 2 colors
        {{{WHITE, GO_UP},
          {BLACK, GO_DOWN}}},

         // 3D simulation with 8 colors
        {{{RED, GO_DOWN},
          {BLACK, GO_BACK},
          {BLUE, DO_NOTHING},
          {MAGENTA, GO_BACK},
          {WHITE, GO_DOWN},
          {GREEN, GO_FRONT},
          {ORANGE, GO_RIGHT},
          {YELLOW, GO_LEFT}}},

         // Stairs
        {{{ORANGE, GO_BACK},
          {WHITE, GO_UP},
          {BLACK, GO_DOWN}}},

        {{{ORANGE, GO_BACK},
          {MAGENTA, GO_LEFT},
          {GREEN, DO_NOTHING},
          {BLACK, GO_UP}}},

        {{{ORANGE, GO_BACK},
          {BLUE, GO_LEFT},
          {BLACK, GO_DOWN}}},

        {{{WHITE, GO_FRONT},
          {RED, GO_BACK},
          {GREEN, GO_BACK}}},

        {{{WHITE, GO_FRONT},
          {RED, GO_FRONT},
          {GREEN, GO_FRONT},
          {BLUE, GO_BACK},
          {YELLOW, GO_FRONT},
          {MAGENTA, GO_BACK},
          {BLACK, GO_FRONT}}},

        {{{WHITE, GO_FRONT},
          {RED, GO_FRONT},
          {GREEN, GO_FRONT},
          {BLUE, GO_BACK},
          {YELLOW, GO_FRONT}}}
};

class Rules {
public:
    Rules(RuleDefinition ruleDefinition = {{{}}});
    void add(std::string color, Move rule);
    void add(Color color, Move rule);

    void loadRule(RuleDefinition rules);

    void reset();

    std::vector<Color> getListColors();

    Orientation getNewOrientation(Orientation currentOrientation, Color cubeColor);

    Color nextColor(Color color);

private:
    Move getRule(Color color);

    std::vector<std::pair<Color, Move>> _listRules;
};


#endif //LANGTON3D_RULES_H
