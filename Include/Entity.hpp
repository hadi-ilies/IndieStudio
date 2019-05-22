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
    bool changeModel(const std::string &model);
    bool changeTexture(const std::string &texture);
    void aff();

private:
    void getModel(const std::string &fileName);
    void getTexture(const std::string &fileName);

protected:
    Window &window;
    IAnimatedMeshSceneNode *mesh;
    World &world;
    vector3du pos;

private:
    std::string textureUse;
    std::map<std::string, IAnimatedMesh*> modelMap;
    std::map<std::string, ITexture*> textureMap;
};

#endif
