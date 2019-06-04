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
#include "Block.hpp"

#include <irrlicht/irrlicht.h>
#include "Window.hpp"

using namespace std;
using namespace irr;

using namespace core; // tmp
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class World
{
public:
    World(Window *_window, const std::string &_fileName); // TODO
    ~World();
    const vector3du &getSize() const;
    const Block *getBlock(const vector3du &pos) const;
    void explode(const vector3du &pos, const uint &power); // ? explode 2D or 3D // TODO ?
    bool load(const std::string &_fileName);
    bool save(const std::string &_fileName = "");
    void update();

private:
    void create(const vector3du &_size);
    bool addBlock(const vector3du &pos, const std::string &type);
    bool removeBlock(const vector3du &pos);

private:
    std::string fileName;
    Window *window;
    vector3du size;
    Block ****tab;
};

#endif
