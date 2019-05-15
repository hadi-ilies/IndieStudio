/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Block.hpp
*/

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>
#include <map> // ?

class Block
{
public:
    Block(const string &fileName); // TODO
    ~Block();
    const string &getType() const;
    const bool &getOpaque() const;

private:
    string type;
    bool opaque;
    // TODO add var (sprite and texture ?)
};

const map<string, unique_ptr<Block>> createBlockMap(const string &path = "Resources/Block");

#endif
