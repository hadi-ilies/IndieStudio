/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Entity.cpp
*/

#include "Entity.hpp"

Entity::Entity(Window &window, const std::string &fileName, World &_world, const vector3du &_pos)
    : mech(window.addAnimatedMesh(fileName + "/Model.md2", fileName + "/Texture.png")), world(_world), pos(_pos)
{
}

Entity::~Entity()
{
}

const vector3du &Entity::getPos() const
{
    return pos;
}

void Entity::aff()
{
    if (mech)
        mech->setPosition(vector3df(pos.X * 10, pos.Z * 10, pos.Y * 10));
}
