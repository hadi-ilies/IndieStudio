/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Entity.cpp
*/

#include "Entity.hpp"

Entity::Entity(const vector3du &_pos)
    : pos(_pos)
{
}

Entity::~Entity()
{
}

const vector3du &Entity::getPos() const
{
    return pos;
}
