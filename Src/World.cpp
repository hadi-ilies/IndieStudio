/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** World.cpp
*/

#include <vector>
#include "World.hpp"

World::World(Window &_window, const std::string &_fileName)
    : window(_window) // tmp
{
    create(vector3du(20, 2, 20));
    for (uint i = 0; i < size.X; i++) // tmp
        for (uint j = 0; j < size.Z; j++) {
            tab[i][0][j].type = "Wall";
            if (i == 0 || j == 0 || i == size.X - 1 || j == size.Z - 1)
                tab[i][1][j].type = "Wall";
            else
                if (rand() % 2)
                    tab[i][1][j].type = "Box";
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

#include <iostream>
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
            if (!tab[newPos.X][newPos.Y][newPos.Z].type.empty()) {
                if (tab[newPos.X][newPos.Y][newPos.Z].type == "Box") // tmp use getDestructible of block
                    tab[newPos.X][newPos.Y][newPos.Z].type = "";
                dirList[j] = vector3du(0, 0, 0);
            }
        }
    }
}

void World::aff()
{
    for (uint i = 0; i < size.X; i++)
        for (uint j = 0; j < size.Y; j++)
            for (uint k = 0; k < size.Z; k++)
                if (!tab[i][j][k].type.empty()) {
                    const std::string fileName = "Resources/Block/" + tab[i][j][k].type + "/Texture.png"; // tmp
                    ISceneNode *node = window.addCube(fileName); // tmp

                    if (node)
                        node->setPosition(vector3df(i, j, k));
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
