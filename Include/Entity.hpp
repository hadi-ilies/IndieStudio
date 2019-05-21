/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Entity.hpp
*/

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <map>
#include "World.hpp"

class Entity
{
public:
    Entity(Window &_window, const std::string &fileName, World &world, const vector3du &_pos); // ? fileName
    ~Entity();
    const vector3du &getPos() const;
    void aff();

private:
    void getModel(const std::string &fileName);

protected:
    Window &window;
    std::map<std::string, IAnimatedMesh*> modelMap; // TODO private and add function changeModel
    IAnimatedMeshSceneNode *mesh;
    World &world;
    vector3du pos;
};

#endif
