/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, OOP_indie_studio_2018, Zappy group
 * @package Entity
 * @file Bomb
 */

#ifndef BOMB_HPP
#define BOMB_HPP

#include <iostream>

#include "Entity.hpp"

using namespace std;

class Bomb : public Entity {
public:
    Bomb(Window *window, const std::string &_type, const uint &_power, World *world, const vector3du &pos);
    ~Bomb();
    const std::string &getType() const;
    const uint &getPower() const;
    const uint &getTick() const;

public:
    void update() override;
    void detonate();

private:
    std::string type;
    uint power;
    uint tick;
};

#endif /* !BOMB_HPP */
