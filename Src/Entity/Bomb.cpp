/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Bomb.cpp
*/

#include "Bomb.hpp"

Bomb::Bomb(const string &_type, const uint &_power, World &world, const vector3du &pos)
    : Entity(world, pos), type(_type), power(_power)
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

private:
    string type;
    uint power;
};

#endif
