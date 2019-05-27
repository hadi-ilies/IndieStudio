/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Entity.cpp
*/

#include <regex>
#include "Entity.hpp"
#include "Globpp.hpp"

#include <iostream> // tmp
Entity::Entity(Window &_window, const std::string &fileName, World &_world, const vector3du &_pos)
    : window(_window), mesh(_window.addAnimatedMesh(fileName + "/Model/Idle.md2", fileName + "/Texture/Default.png")), world(_world), pos(_pos), modelUse("Idle"), textureUse("Default")
{
    if (!mesh)
        throw Error("mesh can't be create");
    const core::aabbox3d<f32> boundingBox = mesh->getTransformedBoundingBox();
    const vector3df size = boundingBox.getExtent();
    float scale = 1 / size.X;

    mesh->setAnimationSpeed(350); // ?
    getModel(fileName + "/Model"); // TODO set in init
    getTexture(fileName + "/Texture"); // TODO set in init
    if (1 / size.Y < scale)
        scale = 1 / size.Y;
    if (1 / size.Z < scale)
        scale = 1 / size.Z;
    mesh->setScale(vector3df(scale, scale, scale));
}

Entity::~Entity()
{
    mesh->remove();
}

const vector3du &Entity::getPos() const
{
    return pos;
}

bool Entity::changeModel(const std::string &model)
{
    if (model == modelUse)
        return false;
    if (modelMap.find(model) == modelMap.end())
        return false;
    mesh->setMesh(modelMap[model]);
    changeTexture(textureUse);
    modelUse = model;
    return true;
}

bool Entity::changeTexture(const std::string &texture)
{
    if (textureMap.find(texture) == textureMap.end())
        return false;
    mesh->setMaterialFlag(EMF_LIGHTING, false);
    mesh->setMaterialTexture(0, textureMap[texture]);
    textureUse = texture;
    return true;
}

void Entity::update()
{
    mesh->setPosition(vector3df(pos.X, pos.Y, pos.Z));
}

void Entity::getModel(const std::string &fileName)
{
    const vector<std::string> modelStrList = globpp(fileName + "/*");
    smatch match;

    for (const std::string &modelStr : modelStrList)
        if (regex_search(modelStr, match, regex(R"(/(\w+).md2$)")))
            if (IAnimatedMesh *model = window.getModel(modelStr))
                modelMap[match[1]] = model;
}

void Entity::getTexture(const std::string &fileName)
{
    const vector<std::string> textureStrList = globpp(fileName + "/*");
    smatch match;

    for (const std::string &textureStr : textureStrList)
        if (regex_search(textureStr, match, regex(R"(/(\w+).png)")))
            if (ITexture *texture = window.getTexture(textureStr))
                textureMap[match[1]] = texture;
}
