/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** World.hpp
*/

#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <memory> // ?
//#include "Block.hpp" // TODO

#include <irrlicht/irrlicht.h>
#include "Window.hpp"

using namespace std;
using namespace irr;

using namespace core; // tmp
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

typedef vector3d<uint> vector3du; // ? move in Type.hpp

struct Tab
{
    std::string type;
    //unique_ptr<Block> block;
};

class World
{
public:
    World(Window &_window, const std::string &_fileName); // TODO
    ~World();
    const vector3du &getSize() const;
    const Tab &getTab(const vector3du &pos) const;
    void setTab(const vector3du &pos, const Tab &_tab); // ?
    void explode(const vector3du &pos, const uint &power); // ? explode 2D or 3D // TODO ?
    void aff(); // TODO
    void debugAff() const; // tmp

private:
    void create(const vector3du &_size);

private:
    Window &window;
    vector3du size;
    Tab ***tab;
};

#endif
