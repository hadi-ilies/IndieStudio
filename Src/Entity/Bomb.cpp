/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Bomb.cpp
*/

#include "Entity/Bomb.hpp"

Bomb::Bomb(Window &window, const std::string &_type, const uint &_power, World &world, const vector3du &pos)
    : Entity(window,"Resources/Entity/Bomb" + _type, world, pos), type(_type), power(_power)
{
    // TODO ? put a invisible block
}

Bomb::~Bomb()
{
    // TODO ? remove the invisible block
}

void Bomb::detonate()
{
    world.explode(pos, power);
}
