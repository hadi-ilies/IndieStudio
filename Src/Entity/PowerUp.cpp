/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** PowerUp.cpp
*/

#include "PowerUp.hpp"

PowerUp::PowerUp(const std::string &_type, World &world, const Vector3u &pos)
    : Entity(world, pos), type(_type)
{
}

PowerUp::~PowerUp()
{
}
