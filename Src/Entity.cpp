/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Entity.cpp
*/

#include "Entity.hpp"

Entity::Entity(Window &_window, const std::string &fileName, World &_world, const vector3du &_pos)
    : window(_window), mesh(_window.addAnimatedMesh(fileName + "/Model.md2", fileName + "/Texture.png")), world(_world), pos(_pos)
{
    const vector3df size = mesh->getTransformedBoundingBox().getExtent();
    float scale = 1 / size.X;

    if (1 / size.Y < scale)
        scale = 1 / size.Y;
    if (1 / size.Z < scale)
        scale = 1 / size.Z;
    mesh->setScale(vector3df(scale, scale, scale));
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
    mesh->setPosition(vector3df(pos.X, pos.Y, pos.Z));
}
