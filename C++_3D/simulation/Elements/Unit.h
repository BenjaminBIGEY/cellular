//
// Created by benji on 24/10/16.
//

#ifndef C_3D_UNIT_H
#define C_3D_UNIT_H

#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec4.hpp>

enum Color {
    WHITE = 0,
    RED = 1,
    GREEN = 2,
    BLACK = 3,
    BLUE = 4,
    YELLOW = 5,
    ORANGE = 6,
    MAGENTA = 7,

    NBR = 8,
};

class Unit {
public:
    Unit(Color c = (Color)0);

    Color getColor();

    void setColor(Color c);

    Color operator++(int);

    // Get float values of each Color // TODO change with the ant rules
    static glm::vec3 getColor(Color color);

private:
    Color _color;
};


#endif //C_3D_UNIT_H
