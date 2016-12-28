//
// Created by benji on 26/11/16.
//

#ifndef LANGTON3D_COLOR_H
#define LANGTON3D_COLOR_H

#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec4.hpp>

#include "../Message_Colors.h"

#define COLORS_NUMBER 12

enum AllColors {
    WHITE = 0,
    RED,
    GREEN,
    BLACK,
    BLUE,
    YELLOW,
    ORANGE,
    MAGENTA,
    BROWN,
    GREY,
    PURPLE,
    CYAN,

    NULL_COLOR
};

class Color {
public:
    Color(AllColors c = NULL_COLOR);
    Color(std::string color);

    AllColors getColor();
    glm::vec3 getColorGraphic();
    std::string getColorName();

    void setColor(AllColors c);
    bool setColor(std::string color);

    bool exists();
    bool equal(const Color &other) const;
    bool less(const Color &other) const;

private:
    AllColors _color;
};

constexpr bool operator==(Color const& c1, Color const& c2) {return c1.equal(c2);}
constexpr bool operator!=(Color const& c1, Color const& c2) {return !(c1==c2);}
constexpr bool operator< (Color const& c1, Color const& c2) {return c1.less(c2);}


#endif //LANGTON3D_COLOR_H
