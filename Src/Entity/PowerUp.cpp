/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** PowerUp.cpp
*/

#include "Entity/PowerUp.hpp"

PowerUp::PowerUp(Window *window, const std::string &_type, World *world, const vector3du &pos)
    : Entity(window, _type, world, pos), type(_type)
{
}

PowerUp::~PowerUp()
{
}
