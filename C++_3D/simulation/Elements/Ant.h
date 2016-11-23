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
    GO_BACK,
    GO_RIGHT,
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
        Rule{Color::WHITE, GO_RIGHT, 1},
        Rule{Color::RED, GO_LEFT, 1},
        Rule{Color::GREEN, GO_RIGHT, 1},
        Rule{Color::BLACK, GO_LEFT, 1},
        Rule{Color::BLUE, GO_RIGHT, 1},
        Rule{Color::YELLOW, GO_LEFT, 1},
        Rule{Color::ORANGE, GO_RIGHT, 1},
        Rule{Color::MAGENTA, GO_LEFT, 1}
}};

/************************************************************************/

// Orientation of the ant at the instant t
enum Orientation {
    FRONT = 0,  // +X
    BACK,       // -X
    RIGHT,      // +Y
    LEFT,       // -Y
    UP,         // +Z
    DOWN        // -Z
};

class Ant {
public:
    Ant(Vector3 position, Orientation orientation);

    Vector3 getPosition();

    Orientation getOrientation();
    void setOrientation(Orientation orientation);

    void update(Color color);

protected:
    void turn(Color color);
    void move(int incrementing);

private:
    Vector3 _position;

    Orientation _orientation;
};


#endif //C_3D_ANT_H
