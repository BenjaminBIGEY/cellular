//
// Created by benji on 24/10/16.
//

#ifndef C_3D_ANT_H
#define C_3D_ANT_H

#include <array>

#include "../CubeMap.h"
#include "Rules.h"

class Ant {
public:
    Ant(Vector3 position, Orientation orientation);

    Vector3 getPosition();

    Orientation getOrientation();
    void setOrientation(Orientation orientation);

    void update(Color color, std::shared_ptr<Rules> rules);

protected:
    void move(int incrementing);

private:
    Vector3 _position;

    Orientation _orientation;
};


#endif //C_3D_ANT_H
