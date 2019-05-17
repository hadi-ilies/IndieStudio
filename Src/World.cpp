/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** World.cpp
*/

#include "World.hpp"

World::World(Window &_window, const std::string &_fileName)
    : window(_window) // tmp
{
    create(vector3du(30, 30, 2));
    for (uint i = 0; i < size.X; i++) // tmp
        for (uint j = 0; j < size.Y; j++) {
            tab[i][j][0].type = "Wall";
            if (i == 0 || j == 0 || i == size.X - 1 || j == size.Y - 1)
                tab[i][j][1].type = "Wall";
            else
                if (rand() % 2)
                    tab[i][j][1].type = "Box";
        }
}

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

const Tab &World::getTab(const vector3du &pos) const
{
    return tab[pos.X][pos.Y][pos.Z];
}

void World::setTab(const vector3du &pos, const Tab &_tab)
{
    tab[pos.X][pos.Y][pos.Z] = _tab; // ?
}

void World::explode(const vector3du &pos, const uint &power)
{
    // TODO
}

void World::aff()
{
    for (uint i = 0; i < size.X; i++)
        for (uint j = 0; j < size.Y; j++)
            for (uint k = 0; k < size.Z; k++)
                if (!tab[i][j][k].type.empty()) {
                    const std::string fileName = "Resources/Block/" + tab[i][j][k].type + "/Texture.png"; // tmp
                    ISceneNode *node = window.addCube(10, fileName); // tmp

                    if (node)
                        node->setPosition(vector3df(i * 10, k * 10, j * 10));
                }
}

#include <iostream> // tmp
void World::debugAff() const
{
    cerr << "size : (" << size.X << ", " << size.Y << ", " << size.Z << ")" << endl;
    for (uint k = 0; k < size.Z; k++) {
        for (uint j = 0; j < size.Y; j++) {
            for (uint i = 0; i < size.X; i++)
                cerr << "\"" << tab[i][j][k].type << "\" ";
            cerr << endl;
        }
        cerr << endl;
    }
}

void World::create(const vector3du &_size)
{
    size = _size;
    tab = new Tab** [size.X];
    for (uint i = 0; i < size.X; i++) {
        tab[i] = new Tab* [size.Y];
        for (uint j = 0; j < size.Y; j++)
            tab[i][j] = new Tab [size.Z];
    }
}
