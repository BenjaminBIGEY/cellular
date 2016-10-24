#include <iostream>
#include "World/World.h"


int main() {
    World world(10, 10, 10);
    world.addAnt(5, 5, 5);
    std::cout << "hello, it's me";
    /*std::deque<std::deque<int>> list;
    for(int i = 0;i<20;i++) {
        std::deque<int> v;
        for(int j = 0;j<10;j++) {
            v.emplace_back(4);
        }
        list.push_back(v);
    }

    list[1].clear();
    list.clear();
    std::cout << list.size();

    for(int i = 0;i<list.size();i++){
        std::cout << i << " : ";
        for(int j=0;j<list[j].size();j++){
            std::cout << list[i][j] << " ";
        }
        std::cout << '\n';
    }*/
    return 0;
}