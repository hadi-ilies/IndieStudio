/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb.cpp
*/

#include "Entity/Bomb.hpp"

/*
 * Constructors // Destructors
 */
Bomb::Bomb(Window *window, const std::string &_type, const uint &_power, World *world, const vector3du &position)
    : Entity(window, "Bomb" + _type, world, position),
      type(_type), power(_power), tick(8)
{
    if (window)
        JukeBox::getInstance().addSound("Explosion", "Resources/Sound/BombExplosion.ogg");
    // TODO ? put a invisible block
}

Bomb::~Bomb()
{
    // TODO ? remove the invisible block
}

/*
 * Getters // Setters
 */
const std::string &Bomb::getType() const
{
    return type;
}

const uint &Bomb::getPower() const
{
    return power;
}

const uint &Bomb::getTick() const
{
    return tick;
}

/*
 * Methods
 */
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

void Bomb::detonate()
{
    if (window)
        JukeBox::getInstance().playSound("Explosion");
    if (world) // ?
        world->explode(position, power);
    power = 0;
}
