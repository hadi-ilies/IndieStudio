/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Bomb.cpp
*/

#include "Entity/Bomb.hpp"

Bomb::Bomb(Window *window, const std::string &_type, const uint &_power, World *world, const vector3du &position)
    : Entity(window, "Bomb" + _type, world, position), type(_type), power(_power), tick(8)
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
    if (world->getBlock(position) && world->getBlock(position)->getType() == "Fire")
        tick = 0;
    if (tick == 0)
        detonate();
    else
        tick--;
}

#include <iostream> // tmp
void Bomb::detonate()
{
    world->explode(position, power);
    power = 0;
    cerr << "BOOMMMMM !!!!!" << endl;
}
