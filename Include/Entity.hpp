/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Entity.hpp
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string> // ?
#include <irrlicht.h> // tmp

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

typedef vector3d<uint> vector3du; // ? move in Type.hpp

class Entity
{
public:
    Entity(const vector3du &_pos);
    ~Entity();
    const vector3du &getPos() const;

private:
    vector3du pos;
};

#endif
