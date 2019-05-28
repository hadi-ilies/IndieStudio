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
    Entity(Window *_window, const std::string &_fileName, World *world, const vector3du &_pos); // ? fileName
    ~Entity();
    const vector3du &getPos() const;
    const std::string &getFileName() const;
    const std::string &getModel() const;
    const std::string &getTexture() const;
    bool changeModel(const std::string &model);
    bool changeTexture(const std::string &texture);
    void update();

private:
    void getModel(const std::string &fileName);
    void getTexture(const std::string &fileName);

protected:
    Window *window;
    IAnimatedMeshSceneNode *mesh;
    World *world;
    vector3du pos;

private:
    const std::string fileName;
    std::string modelUse;
    std::string textureUse;
    std::map<std::string, IAnimatedMesh*> modelMap;
    std::map<std::string, ITexture*> textureMap;
};

#endif
