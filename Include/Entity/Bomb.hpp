/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Bomb.hpp
*/

#ifndef BOMB_HPP
#define BOMB_HPP

#include "Entity.hpp"

class Bomb : public Entity
{
public:
    Bomb(const string &_type, const uint &_power, World &world, const vector3du &pos);
    ~Bomb();
    void detonate(); // ? const

private:
    string type; // ?
    uint power;
};

#endif
