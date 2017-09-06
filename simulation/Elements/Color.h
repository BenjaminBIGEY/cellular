//
// Created by benji on 26/11/16.
//

#ifndef LANGTON3D_COLOR_H
#define LANGTON3D_COLOR_H

#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec4.hpp>
#include <tuple>

#include "../Message_Colors.h"

#define COLORS_NUMBER 16

enum class AllColors {
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
    PINK,
    BRONZE,
    COFFEE,
    CORAL,

    NULL_COLOR
};

class Color {
public:
    Color(AllColors c = AllColors::NULL_COLOR);
    Color(std::string color);

    AllColors getColor();
    glm::vec3 getColorGraphic();
    std::string getColorName();

    void setColor(AllColors c);
    bool setColor(std::string color);

    bool exists();
    bool equal(const Color &other) const;
    bool less(const Color &other) const;

    const std::tuple<AllColors> tie() const { return std::tie(_color); }
    
    friend bool operator==(const Color& c1, const Color& c2) { return c1.tie() == c2.tie(); }
    friend bool operator!=(const Color& c1, const Color& c2) { return !(c1 == c2); }
    friend bool operator< (const Color& c1, const Color& c2) { return c1.tie() < c2.tie(); }

private:
    AllColors _color;
};

#endif //LANGTON3D_COLOR_H
