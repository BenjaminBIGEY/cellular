//
// Created by benji on 07/11/16.
//

#ifndef LANGTON3D_LIGHT_H
#define LANGTON3D_LIGHT_H


class Context;


class Light {
public :
    Light(float x = 0, float y = 0, float z = 0);

    void pushLight(Context *context);
private :
    float _x, _y, _z;
};


#endif //LANGTON3D_LIGHT_H
