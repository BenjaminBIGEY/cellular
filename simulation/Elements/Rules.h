//
// Created by benji on 26/11/16.
//

#ifndef LANGTON3D_RULES_H
#define LANGTON3D_RULES_H

#include <vector>
#include <map>

#include "../Message_Colors.h"
#include "Color.h"

#define PRE_CONFIGURED_RULES_NUMBER 14

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
    GO_FRONT = 0,
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
        {{{WHITE,   GO_RIGHT},
          {RED,     GO_LEFT}}},

        {{{WHITE,   GO_FRONT},
          {RED,     GO_UP},
          {GREEN,   GO_DOWN}}},

        // (Y, Z) place with 2 colors
        {{{WHITE,   GO_DOWN},
          {RED,     DO_NOTHING}}},

         // 3D simulation with 8 colors
        {{{RED,     GO_DOWN},
          {BLACK,   GO_BACK},
          {BLUE,    DO_NOTHING},
          {MAGENTA, GO_BACK},
          {WHITE,   GO_DOWN},
          {GREEN,   GO_FRONT},
          {ORANGE,  GO_RIGHT},
          {YELLOW,  GO_LEFT}}},

         // Stairs
        {{{BLUE,    GO_BACK},
          {YELLOW,  GO_UP},
          {GREY,    GO_BACK}}},

        {{{ORANGE,  GO_UP},
          {BLUE,    GO_BACK}}},

        {{{MAGENTA, GO_DOWN},
          {RED,     GO_UP},
          {ORANGE,  GO_LEFT},
          {CYAN,    DO_NOTHING}}},

        {{{ORANGE,  GO_BACK},
          {MAGENTA, GO_LEFT},
          {GREEN,   DO_NOTHING},
          {BLACK,   GO_UP}}},

        {{{ORANGE,  GO_BACK},
          {BLUE,    GO_LEFT},
          {BLACK,   GO_DOWN}}},

        {{{WHITE,   GO_FRONT},
          {RED,     GO_BACK},
          {GREEN,   GO_BACK}}},

        {{{WHITE,   GO_FRONT},
          {RED,     GO_FRONT},
          {GREEN,   GO_FRONT},
          {BLUE,    GO_BACK},
          {YELLOW,  GO_FRONT},
          {MAGENTA, GO_BACK},
          {BLACK,   GO_FRONT}}},

        {{{WHITE,   GO_FRONT},
          {RED,     GO_FRONT},
          {GREEN,   GO_FRONT},
          {BLUE,    GO_BACK},
          {YELLOW,  GO_FRONT}}},

        {{{RED,     GO_LEFT},
          {GREEN,   GO_RIGHT},
          {CYAN,    GO_RIGHT},
          {YELLOW,  GO_RIGHT},
          {PURPLE,  GO_RIGHT},
          {GREY,    GO_LEFT},
          {BLACK,   GO_LEFT},
          {BROWN,   GO_LEFT},
          {BLUE,    GO_RIGHT},
          {MAGENTA, GO_RIGHT},
          {WHITE,   GO_RIGHT}}},

        {{{RED,     GO_LEFT},
          {GREEN,   GO_DOWN},
          {BLUE,    GO_FRONT},
          {ORANGE,  GO_RIGHT}}}
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

    std::string getRules();

    Orientation getInitOrientation();

private:
    Move getRule(Color color);

    std::vector<std::pair<Color, Move>> _listRules;

    // Current orientation :                       Front  Back        Right  Left        Up     Down         Move
    const Orientation ORIENTATION_CHANGES[6][6] = {{DOWN,  UP,        FRONT, BACK,      FRONT, BACK},    // GO_Front
                                                   {UP,    DOWN,      BACK,  FRONT,     BACK,  FRONT},   // GO_Back

                                                   {RIGHT, LEFT,      BACK,  FRONT,     RIGHT, LEFT},    // GO_Right
                                                   {LEFT,  RIGHT,     FRONT, BACK,      LEFT,  RIGHT},   // GO_Left

                                                   {UP,    DOWN,      UP,    DOWN,      LEFT,  RIGHT},   // GO_Up
                                                   {DOWN,  UP,        DOWN,  UP,        RIGHT, LEFT}};   // GO_Down

    std::string getMoveName(Move move);
};



#endif //LANGTON3D_RULES_H
