/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Block.hpp
*/

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>
#include <regex>
#include <irrlicht/irrlicht.h>

#include "Window.hpp"
#include "Utility.hpp"
#include "JukeBox.hpp"

using namespace std;
using namespace irr;

using namespace core; // ?
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Block
{
public:
    Block(Window *window, const std::string &_type, const vector3du &position);
    ~Block();
    const std::string &getType() const;
    const bool &getOpaque() const;
    const bool &getDestructible() const;
    const bool &gethalf() const;
    const uint &getLifeTime() const;

public:
    void update();

private:
    void getProperty(const std::string &fileName);

private:
    std::string type;
    bool opaque; // ?
    bool destructible; // ? name
    bool half;
    uint lifeTime;
    ISceneNode *cube;
};

#endif /* !BLOCK_HPP */
