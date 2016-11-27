#include "simulation/Simulation.h"
#include "getopt.h"

using namespace std;

void printHelp() {
    cout << "Usage : langton3D --rules [[int]|new] --speed [int]" << endl;
}

bool parseArgument(int argc, char** argv, Simulation &simu) {
    int arg;
    static struct option long_options[] = {
            {"rules", required_argument, 0, 'r'},
            {"speed", required_argument, 0, 's'},
            {0, 0, 0, 0}
    };

    int long_index = 0;
    while ((arg = getopt_long(argc, argv, "r:s:", long_options, &long_index)) != -1) {

        switch (arg) {
            case 'r' :
                if (std::string(optarg) == "new") {
                    simu.createRules();
                } else if(std::atoi(optarg) < PRE_CONFIGURED_RULES_NUMBER) {
                    simu.setRules(std::atoi(optarg));
                } else {
                    printHelp();
                }
                break;
            /*case 'c' :
                if (std::string(optarg) == "yellow") {
                    color = Constantes::RobotColor::Yellow;
                }
                else if (std::string(optarg) == "blue") {
                    color = Constantes::RobotColor::Blue;
                }
                break;
            case 'w' :
                if (std::string(optarg) == "off") {
                    world = false;
                }*/
                //break;*/
            default :
                printHelp();
                return false;
        }
    }
}

int main(int argc, char** argv) {
    Simulation simu(3);

    //parseArgument(argc, argv, simu);

    //simu.createRules();

    /*RuleDefinition rules;
    rules.addRule(BLUE, GO_FRONT);
    rules.addRule(WHITE, GO_LEFT);
    rules.addRule(GREEN, GO_RIGHT);
    rules.addRule(ORANGE, GO_BACK);
    rules.addRule(RED, GO_UP);
    rules.addRule(MAGENTA, GO_DOWN);

    simu.setRules(rules);*/

    simu.addAnt(0, 0, 0, FRONT);

    simu.start();
    return 0;
}