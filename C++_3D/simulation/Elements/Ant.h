//
// Created by benji on 24/10/16.
//

#ifndef C_3D_ANT_H
#define C_3D_ANT_H

#include <array>

#include "../CubeMap.h"
#include "Unit.h"

/*********
 * RULES *
 *********/

// Rule of each color : ant turn at left or right after the colored square?
enum Move {
    GO_FRONT,
    GO_RIGHT,
    GO_BACK,
    GO_LEFT,
    GO_UP,
    GO_DOWN
};

struct Rule {
    Color color;
    Move rotation;
    int incrementing;
};

const std::array<Rule, (int)Color::NBR> ANT_RULES = {{
        Rule{Color::WHITE, GO_DOWN, 1},
        Rule{Color::BLACK, GO_RIGHT, 1},
        Rule{Color::GREEN, GO_LEFT, 1},
        Rule{Color::RED, GO_RIGHT, 1},
        Rule{Color::BLUE, GO_BACK, 1},
        Rule{Color::YELLOW, GO_UP, 1},
        Rule{Color::ORANGE, GO_FRONT, 1},
}};

/************************************************************************/

// Orientation of the ant at the instant t
enum Orientation {
    FRONT = 0,  // +Y
    RIGHT,      // +X
    BACK,       // -Y
    LEFT,       // -X
    UP,         // +Z
    DOWN        // -Z
};

class Ant {
public:
    Ant(Vector3 position, Orientation orientation);

    Vector3 getPosition();
    Orientation getOrientation();

    void update(Color color);

protected:
    void turn(Color color);
    void move(int incrementing);

private:
    Vector3 _position;

    Orientation _orientation;
};


#endif //C_3D_ANT_H
