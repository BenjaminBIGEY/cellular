//
// Created by benji on 24/10/16.
//

#ifndef C_3D_UNIT_H
#define C_3D_UNIT_H

class Vector3 {
public:
    Vector3(int x, int y, int z) : x(x), y(y), z(z) {}
    int x, y, z;
};

enum Color {
    WHITE = 0,
    BLACK = 1,
    GREEN = 2,
    RED = 3,
    BLUE = 4,
    YELLOW = 5,
    ORANGE = 6,

    NBR = 7,
};

class Unit {
public:
    Unit(Color c = (Color)0);

    Color getColor();
    void setColor(Color c);

    Color operator++(int);

private:
    Color _color;
};


#endif //C_3D_UNIT_H
