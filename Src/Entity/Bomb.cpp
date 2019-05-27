/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Bomb.cpp
*/

#include "Entity/Bomb.hpp"

Bomb::Bomb(Window &window, const std::string &_type, const uint &_power, World &world, const vector3du &pos)
    : Entity(window,"Resources/Entity/Bomb" + _type, world, pos), type(_type), power(_power), tick(9)
{
    // TODO ? put a invisible block
}

Bomb::~Bomb()
{
    // TODO ? remove the invisible block
}

const std::string &Bomb::getType() const
{
    return type;
}

const uint &Bomb::getPower() const
{
    return power;
}

void Bomb::update()
{
    Entity::update();
    if (tick == 0)
        detonate();
    else
        tick--;
}

#include <iostream> // tmp
void Bomb::detonate()
{
    world.explode(pos, power);
    power = 0;
    cerr << "BOOMMMMM !!!!!" << endl;
}
