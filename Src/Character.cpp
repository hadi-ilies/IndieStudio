/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Character.cpp
*/

#include "Character.hpp"

Character::Character(World &world, const Vector3u &pos)
    : Entity(world, pos), speed(1)
{
}

Character::~Character()
{
}

bool Character::move(const Vector2i &dir)
{
    if () // TODO collision
        return false;
    // TODO animation
    pos.x += dir.x;
    pos.y += dir.y;
    return true;
}
