/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Entity.hpp
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "World.hpp"

class Entity
{
public:
    Entity(World &world, const vector3du &_pos);
    ~Entity();
    const vector3du &getPos() const;

protected:
    World &world;
    vector3du pos;
};

#endif
