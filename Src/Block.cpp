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

Block::Block(Window *window, const std::string &_type, const vector3du &position)
    : type(_type), lifeTime(-1), cube(window ? window->addCube("Resources/Block/" + _type + "/Texture.png") : NULL)
{
    getProperty("Resources/Block/" + _type + "/Property"); // TODO set in init
    if (window) {
        const vector3df floatPos(position.X, position.Y, position.Z);

        if (!cube)
            throw Error("cube can't be create");
        cube->setPosition(floatPos);
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

const uint &Block::getLifeTime() const
{
    return lifeTime;
}

void Block::update()
{
    if (lifeTime && lifeTime != -1)
        lifeTime--;
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
        else if (regex_search(line, match, regex(R"(^lifeTime *: *(\d+)$)")))
            destructible = match[1] == stoi(match[1]);
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
