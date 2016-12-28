//
// Created by benji on 20/12/16.
//

#ifndef LANGTON3D_MESSAGE_COLORS_H
#define LANGTON3D_MESSAGE_COLORS_H

#include <iostream>
#include <sstream>
#include <string>

#define RST        "\x1B[0m"

#define _BOLD(x)    "\x1B[1m" x RST

#define _RED(x)     "\x1B[31m" x RST
#define _GREEN(x)   "\x1B[32m" x RST
#define _YELLOW(x)  "\x1B[33m" x RST
#define _BLUE(x)    "\x1B[34m" x RST
#define _MAGENTA(x) "\x1B[35m" x RST
#define _CYAN(x)    "\x1B[36m" x RST
#define _WHITE(x)   "\x1B[37m" x RST

#define _UNDL(x)    "\x1B[4m" x RST

#endif //LANGTON3D_MESSAGE_COLORS_H
