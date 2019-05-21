/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Entity.cpp
*/

#include "Entity.hpp"
#include "Globpp.hpp"

Entity::Entity(Window &_window, const std::string &fileName, World &_world, const vector3du &_pos)
    : window(_window), mesh(_window.addAnimatedMesh(fileName + "/Model/Idle.md2", fileName + "/Texture.png")), world(_world), pos(_pos)
{
    const vector3df size = mesh->getTransformedBoundingBox().getExtent();
    float scale = 1 / size.X;

    getModel(fileName + "/Model"); // TODO set in init
    if (1 / size.Y < scale)
        scale = 1 / size.Y;
    if (1 / size.Z < scale)
        scale = 1 / size.Z;
    mesh->setScale(vector3df(scale, scale, scale));
}

Entity::~Entity()
{
}

const vector3du &Entity::getPos() const
{
    return pos;
}

void Entity::aff()
{
    mesh->setPosition(vector3df(pos.X, pos.Y, pos.Z));
}

void Entity::getModel(const std::string &fileName)
{
    const vector<std::string> modelStrList = globpp(fileName + "/*");

    for (const std::string &modelStr : modelStrList) {
        IAnimatedMesh *model = window.getModel(modelStr);
        std::string name = modelStr.substr(modelStr.rfind("/"));

        if (model)
            modelMap[name] = model;
    }
}
