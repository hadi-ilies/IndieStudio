/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Bomb.cpp
*/

#include "Entity/Bomb.hpp"

/*
 * Constructors // Desctructors
 */
Bomb::Bomb(const std::string &_type, const uint &_power, World *world, const vector3du &position) : Entity("Bomb" + _type, world, position),
                                                                                                    type(_type), power(_power), tick(8) {
    // TODO ? put a invisible block
}

Bomb::~Bomb() {
    // TODO ? remove the invisible block
}

/*
 * Getters // Setters
 */
const std::string &Bomb::getType() const {
    return type;
}

const uint &Bomb::getPower() const {
    return power;
}

/*
 * Methods
 */
void Bomb::update() {
    Entity::update();
    if (world->getBlock(position) && world->getBlock(position)->getType() == "Fire")
        tick = 0;
    if (tick == 0)
        detonate();
    else
        tick--;
}

void Bomb::detonate() {
    world->explode(position, power);
    power = 0;
    cerr << "BOOMMMMM !!!!!" << endl;
}
