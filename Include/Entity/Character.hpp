/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Character.hpp
*/

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entity.hpp"

typedef unsigned float ufloat; // ?

class Character
{
public:
    Character(World &world, const vector3du &pos);
    ~Character();
    bool move(const Vector2f &dir); // ? Vector2f or Vector3f

private:
    ufloat speed;
};

#endif
