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

typedef vector3d<uint> vector3du; // ? move in Type.hpp

struct Tab
{
    std::string type;
};

class World
{
public:
    World(const std::string &_fileName); // TODO
    ~World();
    const vector3du &getSize() const;
    const Tab &getTab(const vector3du &pos) const;
    const void aff(IVideoDriver *driver, ISceneManager *smgr) const;
    const void debugAff() const; // tmp

private:
    World(const vector3du &_size);

private:
    vector3du size;
    Tab ***tab;
};

#endif
