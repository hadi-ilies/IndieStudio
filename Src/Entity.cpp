/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Entity.cpp
*/

#include <regex>
#include "Entity.hpp"
#include "Utility.hpp"

#include <iostream> // tmp
Entity::Entity(Window *_window, const std::string &_fileName, World *_world, const vector3du &_position)
    : window(_window), mesh(_window ? _window->addAnimatedMesh("Resources/Entity/" + _fileName + "/Model/Idle.md2", "Resources/Entity/" + _fileName + "/Texture/Default.png") : NULL), world(_world), position(_position), fileName(_fileName), modelUse("Idle"), textureUse("Default")
{
    if (window) {
        getModel("Resources/Entity/" + fileName + "/Model"); // TODO set in init
        getTexture("Resources/Entity/" + fileName + "/Texture"); // TODO set in init
        if (!mesh)
            throw Error("mesh can't be create");
        mesh->setAnimationSpeed(350); // ?
    }
}

Entity::~Entity()
{
    if (mesh) // ?
        mesh->remove();
}

const vector3du &Entity::getPosition() const
{
    return position;
}

const std::string &Entity::getFileName() const
{
    return fileName;
}

const std::string &Entity::getModel() const
{
    return modelUse;
}

const std::string &Entity::getTexture() const
{
    return textureUse;
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
    mesh->setPosition(vector3df(position.X, position.Y, position.Z));
}

void Entity::getModel(const std::string &_fileName)
{
    const vector<std::string> modelStrList = globpp(_fileName);
    smatch match;

    for (const std::string &modelStr : modelStrList)
        if (regex_search(modelStr, match, regex(R"(/(\w+).md2$)")))
            if (IAnimatedMesh *model = window ? window->getModel(modelStr) : NULL)
                modelMap[match[1]] = model;
}

void Entity::getTexture(const std::string &_fileName)
{
    const vector<std::string> textureStrList = globpp(_fileName);
    smatch match;

    for (const std::string &textureStr : textureStrList)
        if (regex_search(textureStr, match, regex(R"(/(\w+).png)")))
            if (ITexture *texture = window ? window->getTexture(textureStr) : NULL)
                textureMap[match[1]] = texture;
}
