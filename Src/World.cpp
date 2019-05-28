/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** World.cpp
*/

//#include <fstream>
#include <vector>
#include "World.hpp"
#include "Error.hpp"

World::World(Window *_window, const std::string &_fileName)
    : window(_window) // tmp
{
    /*if (!load(_fileName)) // TODO
      throw Error("load faild");*/
    create(vector3du(21, 2, 21)); // tmp
    for (uint i = 0; i < size.X; i++) // tmp
        for (uint j = 0; j < size.Z; j++) {
            addBlock(vector3du(i, 0, j), "Wall");
            if (i == 0 || j == 0 || i == size.X - 1 || j == size.Z - 1)
                addBlock(vector3du(i, 1, j), "Wall");
            else if (((i + 1) * (j + 1)) % 2)
                addBlock(vector3du(i, 1, j), "Box");
        }
}

World::~World()
{
    for (uint i = 0; i < size.X; i++) {
        for (uint j = 0; j < size.Y; j++) {
            for (uint k = 0; k < size.Z; k++)
                removeBlock(vector3du(i, j, k));
            delete [] tab[i][j];
        }
        delete [] tab[i];
    }
    delete [] tab;
}

const vector3du &World::getSize() const
{
    return size;
}

const Block *World::getBlock(const vector3du &pos) const
{
    return tab[pos.X][pos.Y][pos.Z];
}

void World::explode(const vector3du &pos, const uint &power)
{
    vector<vector3du> dirList = {
        vector3du(-1, 0, 0),
        vector3du(1, 0, 0),
        vector3du(0, 0, -1),
        vector3du(0, 0, 1),
        vector3du(0, -1, 0), // ? 3D
        vector3du(0, 1, 0), // ? 3D
    };

    for (uint i = 0; i <= power; i++) {
        for (uint j = 0; j < dirList.size(); j++) {
            const vector3du newPos = pos + dirList[j] * i;

            if (newPos.X >= size.X || newPos.Y >= size.Y || newPos.Z >= size.Z)
                continue;
            if (tab[newPos.X][newPos.Y][newPos.Z]) {
                if (tab[newPos.X][newPos.Y][newPos.Z]->getDestructible()) // tmp use getDestructible of block
                    removeBlock(newPos);
                dirList[j] = vector3du(0, 0, 0);
            }
        }
    }
}

bool load(const std::string &_fileName)
{
    //
    return true;
}

bool save(const std::string &_fileName)
{
    //
    return true;
}

void World::update()
{
    for (uint i = 0; i < size.X; i++)
        for (uint j = 0; j < size.Y; j++)
            for (uint k = 0; k < size.Z; k++)
                if (tab[i][j][k])
                    tab[i][j][k]->setPosition(vector3du(i, j, k)); // ?
}

void World::create(const vector3du &_size)
{
    size = _size;
    tab = new Block*** [size.X];
    for (uint i = 0; i < size.X; i++) {
        tab[i] = new Block** [size.Y];
        for (uint j = 0; j < size.Y; j++) {
            tab[i][j] = new Block* [size.Z];
            for (uint k = 0; k < size.Z; k++)
                tab[i][j][k] = NULL;
        }
    }
}

bool World::addBlock(const vector3du &pos, const std::string &type)
{
    if (tab[pos.X][pos.Y][pos.Z])
        return false;
    tab[pos.X][pos.Y][pos.Z] = new Block(window, type); // ?
    return true;
}

bool World::removeBlock(const vector3du &pos)
{
    if (!tab[pos.X][pos.Y][pos.Z])
        return false;
    delete tab[pos.X][pos.Y][pos.Z];
    tab[pos.X][pos.Y][pos.Z] = NULL;
    return true;
}
