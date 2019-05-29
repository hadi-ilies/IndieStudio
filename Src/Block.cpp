/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Block.cpp
*/

#include <iostream> // ?
#include <fstream> // ?
#include <regex>
#include "Block.hpp"
#include "Globpp.hpp"
#include "Error.hpp"

Block::Block(Window *window, const std::string &_type)
    : type(type), cube(window ? window->addCube("Resources/Block/" + fileName + "/Texture.png") : NULL)
{
    getProperty("Resources/Block/" + fileName + "/Property"); // TODO set in init
    if (window) {
        if (!cube)
            throw Error("cube can't be create");
    }
}

Block::~Block()
{
    cube->remove();
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
    std::string line;
    smatch match;

    if (!file)
        throw Error("\"" + fileName + "\" cant be open");
    while (getline(file, line)) {
        if (regex_search(line, match, regex(R"(^opaque *: *(false|true)$)")))
            opaque = match[1] == "true" ? true : false;
        else if (regex_search(line, match, regex(R"(^destructible *: *(false|true)$)")))
            destructible = match[1] == "true" ? true : false;
    }
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
