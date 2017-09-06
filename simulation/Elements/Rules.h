//
// Created by benji on 26/11/16.
//

#ifndef LANGTON3D_RULES_H
#define LANGTON3D_RULES_H

#include <vector>
#include <map>

#include "../Message_Colors.h"
#include "Color.h"

#define PRE_CONFIGURED_RULES_NUMBER 17

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
        {{{AllColors::WHITE,   GO_RIGHT},
          {AllColors::RED,     GO_LEFT}}},

        {{{AllColors::WHITE,   GO_FRONT},
          {AllColors::RED,     GO_UP},
          {AllColors::GREEN,   GO_DOWN}}},

        // (Y, Z) place with 2 colors
        {{{AllColors::WHITE,   GO_DOWN},
          {AllColors::RED,     DO_NOTHING}}},

         // 3D simulation with 8 colors
        {{{AllColors::RED,     GO_DOWN},
          {AllColors::BLACK,   GO_BACK},
          {AllColors::BLUE,    DO_NOTHING},
          {AllColors::MAGENTA, GO_BACK},
          {AllColors::WHITE,   GO_DOWN},
          {AllColors::GREEN,   GO_FRONT},
          {AllColors::ORANGE,  GO_RIGHT},
          {AllColors::YELLOW,  GO_LEFT}}},

         // Stairs
        {{{AllColors::BLUE,    GO_BACK},
          {AllColors::YELLOW,  GO_UP},
          {AllColors::GREY,    GO_BACK}}},

        {{{AllColors::ORANGE,  GO_UP},
          {AllColors::BLUE,    GO_BACK}}},

        {{{AllColors::MAGENTA, GO_DOWN},
          {AllColors::RED,     GO_UP},
          {AllColors::ORANGE,  GO_LEFT},
          {AllColors::CYAN,    DO_NOTHING}}},

        {{{AllColors::ORANGE,  GO_BACK},
          {AllColors::MAGENTA, GO_LEFT},
          {AllColors::GREEN,   DO_NOTHING},
          {AllColors::BLACK,   GO_UP}}},

        {{{AllColors::ORANGE,  GO_BACK},
          {AllColors::BLUE,    GO_LEFT},
          {AllColors::BLACK,   GO_DOWN}}},

        {{{AllColors::WHITE,   GO_FRONT},
          {AllColors::RED,     GO_BACK},
          {AllColors::GREEN,   GO_BACK}}},

        {{{AllColors::WHITE,   GO_FRONT},
          {AllColors::RED,     GO_FRONT},
          {AllColors::GREEN,   GO_FRONT},
          {AllColors::BLUE,    GO_BACK},
          {AllColors::YELLOW,  GO_FRONT},
          {AllColors::MAGENTA, GO_BACK},
          {AllColors::BLACK,   GO_FRONT}}},

        {{{AllColors::WHITE,   GO_FRONT},
          {AllColors::RED,     GO_FRONT},
          {AllColors::GREEN,   GO_FRONT},
          {AllColors::BLUE,    GO_BACK},
          {AllColors::YELLOW,  GO_FRONT}}},

        {{{AllColors::RED,     GO_LEFT},
          {AllColors::GREEN,   GO_RIGHT},
          {AllColors::CYAN,    GO_RIGHT},
          {AllColors::YELLOW,  GO_RIGHT},
          {AllColors::PURPLE,  GO_RIGHT},
          {AllColors::GREY,    GO_LEFT},
          {AllColors::BLACK,   GO_LEFT},
          {AllColors::BROWN,   GO_LEFT},
          {AllColors::BLUE,    GO_RIGHT},
          {AllColors::MAGENTA, GO_RIGHT},
          {AllColors::WHITE,   GO_RIGHT}}},

        {{{AllColors::RED,     GO_LEFT},
          {AllColors::GREEN,   GO_DOWN},
          {AllColors::BLUE,    GO_FRONT},
          {AllColors::ORANGE,  GO_RIGHT}}},

        {{{AllColors::WHITE,   GO_LEFT},
          {AllColors::RED,     GO_RIGHT},
          {AllColors::GREEN,   GO_LEFT},
          {AllColors::BLACK,   GO_DOWN},
          {AllColors::BLUE,    GO_DOWN},
          {AllColors::YELLOW,  GO_DOWN},
          {AllColors::ORANGE,  GO_UP},
          {AllColors::MAGENTA, GO_LEFT},
          {AllColors::BROWN,   GO_RIGHT},
          {AllColors::GREY,    GO_RIGHT},
          {AllColors::PURPLE,  GO_LEFT},
          {AllColors::CYAN,    GO_LEFT},
          {AllColors::PINK,    GO_LEFT},
          {AllColors::BRONZE,  GO_LEFT}}},

        {{{AllColors::WHITE,   GO_RIGHT},
          {AllColors::RED,     GO_LEFT},
          {AllColors::COFFEE,  GO_UP}}},

        {{{AllColors::WHITE,   GO_RIGHT},
          {AllColors::RED,     GO_RIGHT},
          {AllColors::GREEN,   GO_RIGHT},
          {AllColors::BLACK,   GO_LEFT},
          {AllColors::BLUE,    GO_RIGHT},
          {AllColors::YELLOW,  GO_LEFT},
          {AllColors::ORANGE,  GO_RIGHT}}},
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
    std::string getOrientationName(Orientation orientation);

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
