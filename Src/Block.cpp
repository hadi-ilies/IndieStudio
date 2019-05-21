/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Block.cpp
*/

#include <iostream> // ?
#include <fstream> // ?
#include "Block.hpp"
#include "Globpp.hpp"
#include "Error.hpp"

Block::Block(Window &window, const std::string &fileName)
{
    try {
        getProperty(fileName + "/Property");
        cube = window.addCube(fileName + "/Texture.png");
    }
    catch (const exception &e) {
        cerr << e.what() << endl;
    }
}

Block::~Block()
{
}

const std::string &Block::getType() const
{
    return type;
}

const bool &Block::getOpaque() const
{
    return opaque;
}

const bool &Block::getDestructible() const
{
    return destructible;
}

void Block::setPosition(const vector3du &pos)
{
    const vector3df floatPos(pos.X, pos.Y, pos.Z);

    cube->setPosition(floatPos);
}

void Block::getProperty(const std::string &fileName)
{
    ifstream file(fileName);

    if (!file)
        throw Error("\"" + fileName + "\" cant be open");
    // TODO
}

/*const std::map<std::string, unique_ptr<Block>> createBlockMap(Window &window, const std::string &path)
{
    std::map<std::string, unique_ptr<Block>> blockMap;
    const vector<std::string> blockPathList = globpp(path + "/*");

    for (const std::string &blockPath : blockPathList) {
        try {
            unique_ptr<Block> block(new Block(window, blockPath));

            blockMap[block->getType()] = move(block); // ? it works (to test)
        }
        catch (const exception &e) {
            cerr << e.what() << endl;
        }
    }
    return blockMap;
    }*/
