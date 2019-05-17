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
    Entity(Window &window, const std::string &fileName, World &world, const vector3du &_pos); // ? fileName
    ~Entity();
    const vector3du &getPos() const;
    void aff(); // ? const

protected:
    IAnimatedMeshSceneNode *mech; // TODO
    World &world;
    vector3du pos;
};

#endif
