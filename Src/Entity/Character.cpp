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
    /*if () // TODO collision
      return false;*/
    // TODO animation
    pos.X += dir.X;
    pos.Z += dir.Y; // for Z
    return true;
}
