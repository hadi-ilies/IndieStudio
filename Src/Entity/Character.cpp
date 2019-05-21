/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Character.cpp
*/

#include "Entity/Character.hpp"

Character::Character(Window &window, const std::string &fileName, World &world, const vector3du &pos)
    : Entity(window, fileName, world, pos)
{
}

Character::~Character()
{
}

bool Character::move(const vector2di &dir)
{
    vector3du newPos(pos.X + dir.X, pos.Y, pos.Z + dir.Y); // vct2.Y is the vec3.Z
    if (newPos.X > world.getSize().X || newPos.Y > world.getSize().Y || newPos.Z > world.getSize().Z) // TODO collision
        return false;
    if (world.getBlock(newPos)->getOpaque()) // TODO use getOpaque
        return false;
    // TODO animation
    pos = newPos;
    return true;
}
