/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Entity.cpp
*/

#include "Entity.hpp"

Entity::Entity(World &_world, const vector3u &_pos)
    : world(_world), pos(_pos)
{
}

Entity::~Entity()
{
}

const vector3u &Entity::getPos() const
{
    return pos;
}
