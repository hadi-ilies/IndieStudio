/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** World.hpp
*/

#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include "Block.hpp"

typedef Vector<3, uint> Vector3u; // ? move in Type.hpp

struct Tab
{
    unique_ptr<Block> block;
};

class World
{
public:
    World(const string &_fileName); // TODO
    ~World();
    const Vector3u &getSize() const;
    const Tab &getTab(const Vector3u &pos) const;
    void setTab(const Vector3u &pos, const Tab &tab);
    void explode(const Vector3u &pos, const uint &power); // ? explode 2D or 3D
    //const void aff(IVideoDriver *driver, ISceneManager *smgr) const; // TODO
    const void debugAff() const; // tmp

private:
    World(const vector3du &_size);

private:
    Vector3u size;
    unique_ptr<unique_ptr<unique_ptr<Tab>>> tab;
};

#endif
