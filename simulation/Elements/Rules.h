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
    GO_FRONT,
    GO_BACK,
    GO_RIGHT,
    GO_LEFT,
    GO_UP,
    GO_DOWN,
    DO_NOTHING
};

enum PreConfiguredRules {
    X_Y_PLANE_2COLORS = 0,
    X_Z_PLANE_2COLORS,
    Y_Z_PLANE_2COLORS,
    X_Y_Z_8_COLORS,
    STAIRS,

    NBR_RULES = 5
    // TODO : add great rules
};

class Rules {
public:
    Rules(PreConfiguredRules rules);
    void add(std::string color, Move rule);
    void add(Color color, Move rule);

    void loadPreConfiguredRule(PreConfiguredRules rules);

    void reset();

    std::vector<Color> getListColors();

    Orientation getNewOrientation(Orientation currentOrientation, Color cubeColor);

    Color nextColor(Color color);

private:
    Move getRule(Color color);

    std::vector<std::pair<Color, Move>> _listRules;
};


#endif //LANGTON3D_RULES_H
