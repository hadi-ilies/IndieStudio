/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, Zappy group
 * @file Block
 */

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>
#include <iostream>
#include <regex>
#include <irrlicht/irrlicht.h>

#include "Window.hpp"
#include "Utility.hpp"
#include "JukeBox.hpp"

using namespace std;

/**
 * @namespace Irrlicht
 */
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Block {
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
    bool opaque;
    bool destructible;
    bool half;
    uint lifeTime;
    ISceneNode *cube;
};

#endif /* !BLOCK_HPP */
