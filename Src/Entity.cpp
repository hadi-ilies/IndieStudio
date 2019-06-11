/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Entity.cpp
*/

#include "Entity.hpp"

/*
 * Constructors // Destructors
 */
Entity::Entity(const std::string &_fileName, World *_world, const vector3du &_position) :
    mesh(Window::getInstance().addAnimatedMesh("Resources/Entity/" + _fileName + "/Model/Idle.md2",
                                          "Resources/Entity/" + _fileName + "/Texture/Default.png")),
    world(_world),
    position(_position), fileName(_fileName),
    modelUse("Idle"), textureUse("Default")
{
    init();
    if (!mesh)
        throw Error("Mesh can't be created", __FILE__, __FUNCTION__, __LINE__);
    mesh->setAnimationSpeed(350); // ?
}

Entity::~Entity() {
    if (mesh) // ?
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
    if (modelMap.find(model) == modelMap.end())
        return false;
    mesh->setMesh(modelMap[model]);
    changeTexture(textureUse);
    modelUse = model;
    return true;
}

bool Entity::changeTexture(const std::string &texture) {
    if (textureMap.find(texture) == textureMap.end())
        return false;
    mesh->setMaterialFlag(EMF_LIGHTING, false);
    mesh->setMaterialTexture(0, textureMap[texture]);
    textureUse = texture;
    return true;
}

void Entity::update() {
    mesh->setPosition(vector3df(position.X, position.Y, position.Z));
}

void Entity::getModel(const std::string &_fileName) {
    const vector<std::string> modelStrList = globpp(_fileName);
    smatch match;

    for (const std::string &modelStr : modelStrList)
        if (regex_search(modelStr, match, regex(R"(/(\w+).md2$)")))
            if (IAnimatedMesh *model = Window::getInstance().getModel(modelStr))
                modelMap[match[1]] = model;
}

void Entity::getTexture(const std::string &_fileName) {
    const vector<std::string> textureStrList = globpp(_fileName);
    smatch match;

    for (const std::string &textureStr : textureStrList)
        if (regex_search(textureStr, match, regex(R"(/(\w+).png)")))
            if (ITexture *texture = Window::getInstance().getTexture(textureStr))
                textureMap[match[1]] = texture;
}

void Entity::init() {
    getModel("Resources/Entity/" + fileName + "/Model");
    getTexture("Resources/Entity/" + fileName + "/Texture");
}
