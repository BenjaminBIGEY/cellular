//
// Created by benji on 24/10/16.
//

#ifndef C_3D_WORLD_H
#define C_3D_WORLD_H

#include "Elements/Ant.h"
#include "Elements/Grid3D.h"
#include "Display/Display.h"

#include <unistd.h>
#include <memory>
#include <vector>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class World {
public:
    World(int x, int y, int z);

    void addAnt(int x, int y, int z);

    void update(useconds_t usec); // microseconds

    void debug();

private:
    std::unique_ptr<Grid3D> _grid = nullptr;
    std::vector<std::unique_ptr<Ant>> _listAnts;

    // Counter of moves
    int _count = 0;

};


#endif //C_3D_WORLD_H
