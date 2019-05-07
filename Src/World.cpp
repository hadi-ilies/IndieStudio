/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** World.cpp
*/

#include "World.hpp"

/*World::World(const string &_fileName) // TODO
{
}*/

World::~World()
{
    for (uint i = 0; i < size.X; i++) {
        for (uint j = 0; j < size.Y; j++)
            delete [] tab[i][j];
        delete [] tab[i];
    }
    delete [] tab;
}

const vector3du &World::getSize() const
{
    return size;
}

World::World(const vector3du &_size)
    : size(_size)
{
    tab = new Tab** [size.X];
    for (uint i = 0; i < size.X; i++) {
        tab[i] = new Tab* [size.Y];
        for (uint j = 0; j < size.Y; j++)
            tab[i][j] = new Tab [size.Z];
    }
}
