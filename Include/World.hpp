/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** World.hpp
*/

#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <irrlicht.h> // tmp

using namespace std;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

typedef vector3d<unsigned int> vector3du; // ? move in type.hpp

struct Tab
{
    int id; // tmp
};

class World
{
public:
    //World(const string &_fileName); // TODO
    ~World();
    const vector3du &getSize() const;

private:
    World(const vector3du &_size);

private:
    vector3du size;
    Tab ***tab;
};

#endif
