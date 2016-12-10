//
// Created by benji on 10/11/16.
//

#include "Grid3D.h"


Grid3D::Grid3D(const int radiusSphere) {
    _normRadius.push_back(radiusSphere);
}

void Grid3D::clear() {
    _cubeMap.clear();
}

void Grid3D::reset(vector<Color> listColors) {
    _cubeMap.clear();
    _colorInit = listColors[0];

    for(auto color : listColors) {
        _cubesPtr[color] = std::make_shared<Cube>(color);
    }
}

void Grid3D::update(Vector3 position, std::shared_ptr<Rules> rules) {
    if(cubeIsExisting(position)) {
        setColor(position, rules->nextColor(getColor(position)));
    } else {
        createCube(position, NULL_COLOR);
    }

    if(position.x > _xMax)
        _xMax = position.x;
    else if(position.x < _xMin)
        _xMin = position.x;
    if(position.y > _yMax)
        _yMax = position.y;
    else if(position.y < _yMin)
        _yMin = position.y;
    if(position.z > _zMax)
        _zMax = position.z;
    else if(position.z < _zMin)
        _zMin = position.z;
}

void Grid3D::render(Context *context) {
    for(int radius = 0 ; radius < _normRadius.size() ; radius++) {
        std::map<Vector3, std::shared_ptr<Cube>>::iterator it;
        for(it = _cubeMap[radius].begin() ; it != _cubeMap[radius].end() ; ++it) {
            // first <=> key : glm::vec3 (cubePosition)
            // second <=> mapped_type : std::shared_ptr<Cube>
            if(_eclatedView) {
                Vector3 vect(it->first);
                vect += vect;
                it->second->render(context, vect);
            } else
                it->second->render(context, it->first);
        }
    }
}

void Grid3D::setColor(Vector3 position, Color color) {
    int radius = getRadius(position);
    if(radius > _cubeMap.size())
        _cubeMap.push_back({});
    _cubeMap[radius][position] = _cubesPtr[color];
}

void Grid3D::createCube(Vector3 position, Color color) {
    int radius = getRadius(position);
    if(radius >= _cubeMap.size())
        _cubeMap.push_back({});
    if(color == NULL_COLOR)
        _cubeMap[radius][position] = _cubesPtr[_colorInit];
    else
        _cubeMap[radius][position] = _cubesPtr[color];
}

int Grid3D::getSize() {
    int size = 0;
    for(int radius = 0 ; radius < _normRadius.size() ; radius++) {
        for(std::map<Vector3, std::shared_ptr<Cube>>::iterator it = _cubeMap[radius].begin() ; it != _cubeMap[radius].end() ; ++it) {
            size++;
        }
    }
    return size;
}

Color Grid3D::getColor(Vector3 position) {
    return _cubeMap[getRadius(position)][position]->_color;
}

bool Grid3D::cubeIsExisting(const Vector3 position) {
    int radius = getRadius(position);
    return !(_cubeMap[radius].find(position) == _cubeMap[radius].end());
}

int Grid3D::getRadius(const Vector3 position) {
    int i = 0;
    int norm = position.norm();
    while(norm > _normRadius[i]) {
        if(i == _normRadius.size() - 1) {
            _normRadius.push_back((int)sqrt(sqrt(1.5)*(_normRadius[0] * _normRadius[0] + _normRadius[i] * _normRadius[i])));
        }
        i++;
    }
    return i;
}

void Grid3D::checkEclatedView() {
    _eclatedView = !_eclatedView;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

Cube::Cube(Color color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : _color(color) {
    // Graphic part
    _render = std::make_shared<RenderableCube>(color.getColorGraphic());
    _render->getMaterial().setAmbient(ambient.x, ambient.y, ambient.z);
    _render->getMaterial().setDiffuse(diffuse.x, diffuse.y, diffuse.z);
    _render->getMaterial().setSpecular(specular.x, specular.y, specular.z);
}

void Cube::render(Context *context, Vector3 position) {
    _render->render(context, position.toGlmVec3());
}