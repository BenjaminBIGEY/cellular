//
// Created by benji on 10/11/16.
//

#include "Grid3D.h"

void Grid3D::reset(vector<Color> listColors) {
    _grid3D.clear();
    _colorInit = listColors[0];

    for(auto color : listColors) {
        _cubesPtr[color] = std::make_shared<Unit>(color);
    }
}

void Grid3D::update(Vector3 position, std::shared_ptr<Rules> rules) {
    setCubePosition(position);
    if(currentIterator->first != _subCubePosition)
        generateSubCube();

    updateCube(rules->nextColor(getColor()));
}

void Grid3D::render(Context *context) {
    std::map<Vector3, CubeContainer>::iterator it;

    for(it = _grid3D.begin() ; it != _grid3D.end() ; it++) {
        //drawSubCubes(context, it, RED);

        for(int x = 0 ; x < SIZE_SUB_CUBE ; x++) {
            for(int y = 0 ; y < SIZE_SUB_CUBE ; y++) {
                for(int z = 0 ; z < SIZE_SUB_CUBE ; z++) {
                    if(it->second.subCube[x][y][z] != nullptr) {
                        Vector3 vect(it->first);
                        vect *= Vector3(SIZE_SUB_CUBE, SIZE_SUB_CUBE, SIZE_SUB_CUBE);
                        vect += Vector3(x, y, z);

                        if(_eclatedView)
                            vect += vect;

                        it->second.subCube[x][y][z]->render(context, vect);
                    }
                }
            }
        }

    }
}

void Grid3D::drawSubCubes(Context *context, std::map<Vector3, CubeContainer>::iterator it, Color color) {
    std::shared_ptr<Unit> colorPtr = std::make_shared<Unit>(color);

    for(int x = 0 ; x < SIZE_SUB_CUBE ; x++) {
        for(int y = 0 ; y < SIZE_SUB_CUBE ; y++) {
            Vector3 vect(it->first);
            vect *= Vector3(SIZE_SUB_CUBE, SIZE_SUB_CUBE, SIZE_SUB_CUBE);
            vect += Vector3(x, y, 0);

            if(_eclatedView)
                vect += vect;

            colorPtr->render(context, vect);
            vect += Vector3(0, 0, SIZE_SUB_CUBE);
            colorPtr->render(context, vect);
        }

        for(int z = 0 ; z < SIZE_SUB_CUBE ; z++) {
            Vector3 vect(it->first);
            vect *= Vector3(SIZE_SUB_CUBE, SIZE_SUB_CUBE, SIZE_SUB_CUBE);
            vect += Vector3(x, 0, z);

            if(_eclatedView)
                vect += vect;

            colorPtr->render(context, vect);
            vect += Vector3(0, SIZE_SUB_CUBE, 0);
            colorPtr->render(context, vect);
        }
    }

    for(int y = 0 ; y < SIZE_SUB_CUBE ; y++) {
        for(int z = 0 ; z < SIZE_SUB_CUBE ; z++) {
            Vector3 vect(it->first);
            vect *= Vector3(SIZE_SUB_CUBE, SIZE_SUB_CUBE, SIZE_SUB_CUBE);
            vect += Vector3(0, y, z);

            if(_eclatedView)
                vect += vect;

            colorPtr->render(context, vect);
            vect += Vector3(SIZE_SUB_CUBE, 0, 0);
            colorPtr->render(context, vect);
        }
    }
}

void Grid3D::addCube(Vector3 position, Color color) {
    setCubePosition(position);
    generateSubCube();
    updateCube(color);
}

void Grid3D::updateCube(Color color) {
    if(color == NULL_COLOR)
        _grid3D[_subCubePosition].subCube[_cubePosition.x][_cubePosition.y][_cubePosition.z] = _cubesPtr[_colorInit];
    else
        _grid3D[_subCubePosition].subCube[_cubePosition.x][_cubePosition.y][_cubePosition.z] = _cubesPtr[color];
}

int Grid3D::getSize() {
    int size = 0;
    std::map<Vector3, CubeContainer>::iterator it;
    for(it = _grid3D.begin() ; it != _grid3D.end() ; it++) {
        for(int x = 0 ; x < SIZE_SUB_CUBE ; x++)
            for(int y = 0 ; y < SIZE_SUB_CUBE ; y++)
                for(int z = 0 ; z < SIZE_SUB_CUBE ; z++)
                    if(it->second.subCube[x][y][z] != nullptr)
                        size++;
    }
    return size;
}

int Grid3D::getMaxCoord() {
    int normMax = 0;
    Vector3 coord(0, 0, 0);
    std::map<Vector3, CubeContainer>::iterator it;
    for(it = _grid3D.begin() ; it != _grid3D.end() ; it++) {
        if(it->first.norm() > normMax) {
            coord = it->first;
            normMax = coord.norm();
        }
    }

    if(coord.x > coord.y and coord.x > coord.z)
        return (int)((coord.x + 0.5) * SIZE_SUB_CUBE);
    else if(coord.y > coord.z)
        return (int)((coord.y + 0.5) * SIZE_SUB_CUBE);
    return (int)((coord.z + 0.5) * SIZE_SUB_CUBE);
}

Color Grid3D::getColor() {
        std::shared_ptr<Unit> unit = currentIterator->second.subCube[_cubePosition.x][_cubePosition.y][_cubePosition.z];
    if(unit == nullptr)
        return NULL_COLOR;
    else
        return currentIterator->second.subCube[_cubePosition.x][_cubePosition.y][_cubePosition.z]->_color;
}

void Grid3D::generateSubCube() {
    if(_grid3D.find(_subCubePosition) == _grid3D.end()) {
        CubeContainer subCube;
        for(int x = 0 ; x < SIZE_SUB_CUBE ; x++)
            for(int y = 0 ; y < SIZE_SUB_CUBE ; y++)
                for(int z = 0 ; z < SIZE_SUB_CUBE ; z++)
                    subCube.subCube[x][y][z] = nullptr;

        _grid3D[_subCubePosition] = subCube;

        std::cout << "sub cube generated" << std::endl;
    }

    std::map<Vector3, CubeContainer>::iterator it = _grid3D.begin();
    bool find = false;
    while(!find and it != _grid3D.end()) {
        if(it->first == _subCubePosition) {
            currentIterator = it;
            find = true;
        }
        ++it;
    }
}

void Grid3D::checkEclatedView() {
    _eclatedView = !_eclatedView;
}

void Grid3D::debug() {
    addCube({0, 0, 1}, RED);
    addCube({15, 0, 1}, RED);
    addCube({15, 15, 1}, RED);
    addCube({-14, 0, 1}, RED);
    addCube({-14, -14, 1}, RED);
    addCube({-14, 15, 1}, RED);
    addCube({15, -14, 1}, RED);
    addCube({0, -14, 1}, RED);
    addCube({0, 15, 1}, RED);
    addCube({0, 30, 1}, RED);
    addCube({15, 30, 1}, RED);
    addCube({30, 30, 1}, RED);
    addCube({30, 15, 1}, RED);
    addCube({-14, 30, 1}, RED);
    addCube({30, -14, 1}, RED);
    addCube({30 , 0, 1}, RED);
}

void Grid3D::setCubePosition(Vector3 position) {
    if(position >= Vector3(0, 0, 0)) {
        _cubePosition.x = position.x % SIZE_SUB_CUBE;
        _subCubePosition.x = position.x / SIZE_SUB_CUBE;

        _cubePosition.y = position.y % SIZE_SUB_CUBE;
        _subCubePosition.y = position.y / SIZE_SUB_CUBE;

        _cubePosition.z = position.z % SIZE_SUB_CUBE;
        _subCubePosition.z = position.z / SIZE_SUB_CUBE;
    } /*else {
        std::cerr << "Warning : negative components (possible bugs)" << std::endl;

        if (position.x >= 0) {
            _cubePosition.x = position.x % SIZE_SUB_CUBE;
            _subCubePosition.x = position.x / SIZE_SUB_CUBE;
        } else {
            _subCubePosition.x = (position.x + 1) / SIZE_SUB_CUBE - 1;
            if (abs(position.x) == SIZE_SUB_CUBE)
                _cubePosition.x = SIZE_SUB_CUBE * (position.x / SIZE_SUB_CUBE +
                                                   1);
            else
                _cubePosition.x = SIZE_SUB_CUBE - abs(position.x % SIZE_SUB_CUBE);
        }
    if(position.x >= 0) {
        _cubePosition.x = position.x % SIZE_SUB_CUBE;
        _subCubePosition.x = position.x / SIZE_SUB_CUBE;
    } else {
        _subCubePosition.x = (position.x + 1) / SIZE_SUB_CUBE - 1;
        if(abs(position.x) == SIZE_SUB_CUBE)
            _cubePosition.x = SIZE_SUB_CUBE * (position.x / SIZE_SUB_CUBE +
                    1);
        else
            _cubePosition.x = SIZE_SUB_CUBE - abs(position.x % SIZE_SUB_CUBE);
    }

        if (position.y >= 0) {
            _cubePosition.y = position.y % SIZE_SUB_CUBE;
            _subCubePosition.y = position.y / SIZE_SUB_CUBE;
        } else {
            _subCubePosition.y = (position.y + 1) / SIZE_SUB_CUBE - 1;
            if (abs(position.y) % SIZE_SUB_CUBE == 0)
                _cubePosition.y = SIZE_SUB_CUBE * (position.y / SIZE_SUB_CUBE + 1);
            else
                _cubePosition.y = SIZE_SUB_CUBE - abs(position.y % SIZE_SUB_CUBE);
        }
    if(position.y >= 0) {
        _cubePosition.y = position.y % SIZE_SUB_CUBE;
        _subCubePosition.y = position.y / SIZE_SUB_CUBE;
    } else {
        _subCubePosition.y = (position.y + 1) / SIZE_SUB_CUBE - 1;
        if(abs(position.y) % SIZE_SUB_CUBE == 0)
            _cubePosition.y = SIZE_SUB_CUBE * (position.y / SIZE_SUB_CUBE + 1);
        else
            _cubePosition.y = SIZE_SUB_CUBE - abs(position.y % SIZE_SUB_CUBE);
    }

        if (position.z >= 0) {
            _cubePosition.z = position.z % SIZE_SUB_CUBE;
            _subCubePosition.z = position.z / SIZE_SUB_CUBE;
        } else {
            _subCubePosition.z = (position.z + 1) / SIZE_SUB_CUBE - 1;
            if (abs(position.z) % SIZE_SUB_CUBE == 0)
                _cubePosition.y = SIZE_SUB_CUBE * (position.z / SIZE_SUB_CUBE + 1);
            else
                _cubePosition.z = SIZE_SUB_CUBE - abs(position.z % SIZE_SUB_CUBE);
        }

        Vector3 a = _subCubePosition;
        Vector3 b = _cubePosition;
        Vector3 c = a;
        c *= Vector3(SIZE_SUB_CUBE, SIZE_SUB_CUBE, SIZE_SUB_CUBE);
        c += b;
        if (c != position)
            std::cerr << "différent\n";
    }*/
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

Unit::Unit(Color color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : _color(color) {
    // Graphic part
    _render = std::make_shared<RenderableCube>(color.getColorGraphic());
    _render->getMaterial().setAmbient (ambient.x,  ambient.y,  ambient.z);
    _render->getMaterial().setDiffuse (diffuse.x,  diffuse.y,  diffuse.z);
    _render->getMaterial().setSpecular(specular.x, specular.y, specular.z);
}

void Unit::render(Context *context, Vector3 position) {
    _render->render(context, position.toGlmVec3());
}