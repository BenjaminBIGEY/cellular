#include "simulation/Simulation.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

using namespace std;

void printHelp() {
    cout << "Usage : " _CYAN("langton3D " _BOLD("--rules [[int]|new]\n"))
             _YELLOW(TOSTRING(PRE_CONFIGURED_RULES_NUMBER)) " rules existing\n"
            "To have more help, press " _CYAN("h") " during a simulation." << endl;

    exit(0);
}

int main(int argc, char** argv) {
    int rule = -1;

    for(int i = 0 ; i < argc ; i++) {
        string arg(argv[i]);
        string param;

        if(argc > i + 1 && argv[i + 1][0] != '-') {
            param = string(argv[i + 1]);
        }

        if(arg == "--help" || arg == "-h") {
            printHelp();
        } else if(arg == "--rules" || arg == "-r") {
            if (param == "new") {
                rule = 0;
            } else if(atoi(param.c_str()) <= PRE_CONFIGURED_RULES_NUMBER and atoi(param.c_str()) > 0) {
                rule = atoi(param.c_str());
            } else {
                printHelp();
            }
        }
    }

    if(rule >= 0) {
        Simulation simu;

        simu.addAnt(0, 0, 0);
        simu.addAnt(5, 5, 5);

        if(rule == 0)
            simu.createRules();
        else
            simu.setRules(rule);

        simu.start();
    } else {
        printHelp();
    }
    return 0;
}