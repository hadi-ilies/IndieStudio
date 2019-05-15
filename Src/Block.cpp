/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Block.cpp
*/

#include <iostream> // ?
#include "Block.hpp"
#include "Globpp.hpp"
#include "Error.hpp"

Block::Block(const std::string &fileName)
{
    // TODO
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

const map<std::string, unique_ptr<Block>> createBlockMap(const std::string &path)
{
    map<std::string, unique_ptr<Block>> blockMap;
    const vector<std::string> blockPathList = globpp(path + "/*");

    for (const std::string &blockPath : blockPathList) {
        try {
            unique_ptr<Block> block(new Block(blockPath));

            blockMap[block->getType()] = move(block); // ? it works (to test)
        }
        catch (const exception &e) {
            cerr << e.what() << endl;
        }
    }
    return blockMap;
}
