//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_LIGHT_H
#define LANGTON3D_LIGHT_H


class Context;

enum LightType {
    LIGHT_POINT = 0,
    LIGHT_SUN = 1
};

class Light {
public :
    Light(LightType type = LIGHT_POINT, float x = 0, float y = 0, float z = 0);

    void pushLight(Context *context);
private :
    LightType _type;
    float _x, _y, _z;
};


#endif //LANGTON3D_LIGHT_H
