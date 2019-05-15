/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Character.hpp
*/

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Entity.hpp"

class Character
{
public:
    Character(World &world, const vector3du &pos);
    ~Character();
    bool move(const Vector2f &dir); // ? Vector2f or Vector3f

private:
    float speed;
};

#endif
