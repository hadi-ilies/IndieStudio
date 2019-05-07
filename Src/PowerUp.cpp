/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** PowerUp.cpp
*/

#include "PowerUp.hpp"

PowerUp::PowerUp(const std::string &_type, const vector3du &pos)
    : Entity(pos), type(_type)
{
}

PowerUp::~PowerUp()
{
}
