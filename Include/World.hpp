/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @date © 2019, Zappy group
 * @file World (Map, Map generator)
 */

#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <fstream>
#include <vector>
#include <irrlicht/irrlicht.h>

#include "Utility.hpp"
#include "Block.hpp"
#include "World.hpp"

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

class World {
public:
    World(Window *_window, const vector3du &_size, const uint &seed = time(0));
    World(Window *_window, const std::string &_fileName);
    ~World();
    const vector3du &getSize() const;
    const Block *getBlock(const vector3du &pos) const;

public:
    void explode(const vector3du &pos, const uint &power);
    bool generate(const vector3du &_size, const uint &seed = time(0));
    bool load(const std::string &_fileName);
    bool save(const std::string &_fileName = "");
    void update();

private:
    void create(const vector3du &_size);
    bool addBlock(const vector3du &pos, const std::string &type);
    bool removeBlock(const vector3du &pos);
    bool isValidPosition(int randomPosX, int randomPosZ);
    bool isValidOneP(int posX, int posZ);
    bool isValidTwoP(int posX, int posZ);
    bool isValidThreeP(int posX, int posZ);
    bool isValidFourP(int posX, int posZ);

private:
    std::string fileName;
    Window *window;
    vector3du size;
    Block ****tab;
};

#endif /* !WORLD_HPP */
