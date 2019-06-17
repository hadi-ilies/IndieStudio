/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb.hpp
*/

#ifndef BOMB_HPP
#define BOMB_HPP

#include <iostream>

#include "Entity.hpp"

using namespace std;

class Bomb : public Entity
{
public:
    Bomb(Window *window, const std::string &_type, const uint &_power, World *world, const vector3du &pos);
    ~Bomb();
    const std::string &getType() const;
    const uint &getPower() const;
    const uint &getTick() const;

public:
    void update() override;
    void detonate(); // private ?

private:
    std::string type; // ?
    uint power;
    uint tick; // ? TODO
};

#endif /* !BOMB_HPP */
