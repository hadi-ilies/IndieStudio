/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Entity.cpp
*/

#include "Entity.hpp"

Entity::Entity(World &_world, const Vector3u &_pos)
    : world(_world), pos(_pos)
{
}

Entity::~Entity()
{
}

const Vector3u &Entity::getPos() const
{
    return pos;
}
