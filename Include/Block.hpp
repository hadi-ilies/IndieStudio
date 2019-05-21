/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Block.hpp
*/

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>
//#include <memory> // ?
#include <map> // ?
#include <irrlicht/irrlicht.h>
#include "Window.hpp"

using namespace std;
using namespace irr;

using namespace core; // tmp
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

typedef vector3d<uint> vector3du; // TODO ? move in Type.hpp or Utility.hpp

class Block
{
public:
    Block(Window &window, const std::string &fileName); // TODO
    ~Block();
    const std::string &getType() const;
    const bool &getOpaque() const;
    const bool &getDestructible() const;
    void setPosition(const vector3du &pos);

private:
    void getProperty(const std::string &fileName);

private:
    std::string type;
    bool opaque; // ?
    bool destructible; // ? name
    ISceneNode *cube; // or mesh
};

//const std::map<std::string, unique_ptr<Block>> createBlockMap(Window &window, const std::string &path = "Resources/Block");

#endif
