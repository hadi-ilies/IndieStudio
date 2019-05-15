/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Block.hpp
*/

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>
#include <memory> // ?
#include <map> // ?

using namespace std;

class Block
{
public:
    Block(const std::string &fileName); // TODO
    ~Block();
    const std::string &getType() const;
    const bool &getOpaque() const;

private:
    std::string type;
    bool opaque;
    // TODO add var (sprite and texture ?)
};

const map<std::string, unique_ptr<Block>> createBlockMap(const std::string &path = "Resources/Block");

#endif
