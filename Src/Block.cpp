/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Block.cpp
*/

#include <iostream>
#include "Block.hpp"

Block::Block(const string &fileName)
{
}

Block::~Block()
{
}

const string &Block::getType() const
{
    return type;
}

const bool &Block::getOpaque() const
{
    return opaque;
}

const map<string, unique_ptr<Block>> createBlockMap(const string &path)
{
    map<string, unique_ptr<Block>> blockMap;
    const vector<string> blockPathList = globpp(path + "/*"); // TODO add globpp

    for (const string &blockPath : blockPathList) {
        try {
            unique_ptr<Block> block(blockPath);

            blockMap[block.getType] = block; // ?? it works
        }
        catch (const extension &e) { // TODO add Error
            cerr << e.what() << endl;
        }
    }
    return blockMap;
}
