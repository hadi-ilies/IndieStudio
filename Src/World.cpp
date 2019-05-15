/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** World.cpp
*/

#include "World.hpp"

World::World(const std::string &_fileName)
    : World(vector3du(10, 10, 2)) // tmp
{
    for (uint i = 0; i < size.X; i++) // tmp
        for (uint j = 0; j < size.Y; j++) {
            tab[i][j][0].type = "Wall";
            if (i == 0 || j == 0 || i == 9 || j == 9)
                tab[i][j][1].type = "Wall";
            else
                if (rand() % 5 == 0)
                    tab[i][j][1].type = "Box";
        }
}

World::~World()
{
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

#include <iostream> // tmp
const void World::debugAff() const
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

const void World::aff(IVideoDriver *driver, ISceneManager *smgr) const
{
    for (uint i = 0; i < size.X; i++)
        for (uint j = 0; j < size.Y; j++)
            for (uint k = 0; k < size.Z; k++)
                if (!tab[i][j][k].type.empty()) {
                    //const io::path fileName = L"Resources/Texture/" + tab[i][j][k].type + L".png";
                    scene::ISceneNode *cube = smgr->addCubeSceneNode();

                    if (cube) {
                        //cube->setMaterialTexture(0, driver->getTexture(fileName)); // TODO
                        if (k == 0 || i == 0 || i == 9 || j == 0 || j == 9) // tmp
                            cube->setMaterialTexture(0, driver->getTexture("Resources/Texture/Wall.png")); // tmp
                        else
                            cube->setMaterialTexture(0, driver->getTexture("Resources/Texture/Box.png")); // tmp
                        const aabbox3d<f32> size = cube->getTransformedBoundingBox();
                        cerr << tab[i][j][k].type << ": " << size.MaxEdge.X << " " << size.MaxEdge.Y << " " << size.MaxEdge.Z << endl;
                        cube->setPosition(vector3df(i * 10, j * 10, k * 10));
                    }
                }
}

World::World(const vector3du &_size)
    : size(_size)
{
    /*tab = unique_ptr<Tab[][]>(new Tab** [size.X]);
    for (uint i = 0; i < size.X; i++) {
        tab[i] = unique_ptr<Tab[]>(new Tab* [size.Y]);
        for (uint j = 0; j < size.Y; j++)
            tab[i][j] = unique_ptr<Tab>(new Tab [size.Z]);
            }*/

    tab = new Tab** [size.X];
    for (uint i = 0; i < size.X; i++) {
        tab[i] = new Tab* [size.Y];
        for (uint j = 0; j < size.Y; j++)
            tab[i][j] = new Tab [size.Z];
    }
}
