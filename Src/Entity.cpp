/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Entity.cpp
*/

#include "Entity.hpp"

/*
 * Constructors // Destructors
 */
Entity::Entity(Window *_window, const std::string &_fileName, World *_world, const vector3du &_position)
        : window(_window),
          mesh(_window ? _window->addAnimatedMesh("Resources/Entity/" + _fileName + "/Model/Idle.md2",
                                                  "Resources/Entity/" + _fileName
                                                  + "/Texture/Default.png") : nullptr), world(_world),
          position(_position), fileName(_fileName), modelUse("Idle"), textureUse("Default") {
    getModel("Resources/Entity/" + fileName + "/Model");
    getTexture("Resources/Entity/" + fileName + "/Texture");
    if (window) {
        if (!mesh)
            throw ERROR("Mesh can't be created");
        mesh->setAnimationSpeed(350); // ?
    }
}

Entity::~Entity() {
    if (mesh)
        mesh->remove();
}

/*
 * Getters // Setters
 */
const vector3du &Entity::getPosition() const {
    return position;
}

const std::string &Entity::getFileName() const {
    return fileName;
}

const std::string &Entity::getModel() const {
    return modelUse;
}

const std::string &Entity::getTexture() const {
    return textureUse;
}

/*
 * Methods
 */
bool Entity::changeModel(const std::string &model) {
    if (model == modelUse)
        return false;
    if (window) {
        if (modelMap.find(model) == modelMap.end())
            return false;
        mesh->setMesh(modelMap[model]);
    }
    changeTexture(textureUse);
    modelUse = model;
    return true;
}

bool Entity::changeTexture(const std::string &texture) {
    if (texture == "RANDOM" && textureMap.size() > 0) {
        auto it = textureMap.begin();
        size_t npa = rand() % textureMap.size();

        for (size_t i = 0 ; i < npa ; i++, it++);
        return changeTexture(it->first);
    }
    if (window) {
        if (textureMap.find(texture) == textureMap.end())
            return false;
        mesh->setMaterialFlag(EMF_LIGHTING, false);
        mesh->setMaterialTexture(0, textureMap[texture]);
    }
    textureUse = texture;
    return true;
}

/**
 * Update the map position of the entity
 */
void Entity::update() {
    if (mesh)
        mesh->setPosition(vector3df(position.X, position.Y, position.Z));
}

/**
 * Set a model from a file
 * @param _fileName (File path)
 */
void Entity::getModel(const std::string &_fileName) {
    const vector <std::string> modelStrList = globpp(_fileName);
    smatch match;

    for (const std::string &modelStr : modelStrList)
        if (regex_search(modelStr, match, regex(R"(/(\w+).md2$)")))
            if (IAnimatedMesh * model = window ? window->getModel(modelStr) : nullptr)
                modelMap[match[1]] = model;
}

/**
 * Set a texture from a file
 * @param _fileName (File path)
 */
void Entity::getTexture(const std::string &_fileName) {
    const vector <std::string> textureStrList = globpp(_fileName);
    smatch match;

    for (const std::string &textureStr : textureStrList)
        if (regex_search(textureStr, match, regex(R"(/(\w+).png)")))
            if (ITexture * texture = window ? window->getTexture(textureStr) : nullptr)
                textureMap[match[1]] = texture;
}
