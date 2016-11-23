#include <iostream>
#include "Simulation.h"

#include <map>
int main(int argc, char** argv) {
   /* std::shared_ptr<int> ptr5 = std::make_shared<int>(5);
    std::shared_ptr<int> ptr10 = std::make_shared<int>(10);
    std::shared_ptr<int> ptr0 = std::make_shared<int>(0);
    std::shared_ptr<int> ptr1000 = std::make_shared<int>(1000);
    std::shared_ptr<int> ptr2 = std::make_shared<int>(2);
    std::shared_ptr<int> ptr768 = std::make_shared<int>(768);

    std::map<Vector3, std::shared_ptr<int>> map;
    for(int i = 0 ; i < 10 ; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                Vector3 r(i, j, k);
                if (i % 6 == 0) map[r] = ptr5;
                if (i % 6 == 1) map[r] = ptr10;
                if (i % 6 == 2) map[r] = ptr0;
                if (i % 6 == 3) map[r] = ptr1000;
                if (i % 6 == 4) map[r] = ptr2;
                if (i % 6 == 5) map[r] = ptr768;
            }
        }
    }
    std::cout << "remplissage fini\n\n";
    for(int i = 0 ; i < 10 ; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {

                Vector3 r(i, j, k);
                //std::cout << i << " : " << map[i] << '\n';
                if (map[r] != ptr5
                    and map[r] != ptr10
                    and map[r] != ptr0
                    and map[r] != ptr1000
                    and map[r] != ptr2
                    and map[r] != ptr768)
                    std::cerr << "ERROR : position " << i << ", " << j << ", " << k << '\n';
            }
        }
    }
    std::cout << "done";*/
    Simulation simu;

    //simu.addAnt(10, 10, 10);
    simu.addAnt(0, 0, 0);

    simu.start(1);
    return 0;
}