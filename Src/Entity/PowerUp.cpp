/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** PowerUp.cpp
*/

#include "Entity/PowerUp.hpp"

PowerUp::PowerUp(const std::string &_type, World &world, const Vector3u &pos)
    : Entity(world, pos), type(_type)
{
}

PowerUp::~PowerUp()
{
}
