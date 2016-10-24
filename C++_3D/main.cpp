#include <iostream>
#include "World/World.h"


int main() {
    World world(10, 10, 10);
    world.addAnt(5, 5, 5);

    for(int i = 0 ; i < 100 ; i++) {
        world.update(200000); // update toutes les 0.2s
    }

    return 0;
}