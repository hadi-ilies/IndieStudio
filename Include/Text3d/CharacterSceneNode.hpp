/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** CharacterSceneNode.hpp
*/

#ifndef CHARACTERSCENENODE_HPP
#define CHARACTERSCENENODE_HPP

#include "IrrFont.hpp"

class CharacterSceneNode : public scene::ISceneNode {
public:
    CharacterSceneNode(scene::ISceneManager *smgr, const IrrFont &irrFont); // TODO add position
    const core::aabbox3d<f32> &getBoundingBox() const;
    u32 getMaterialCount() const;
    video::SMaterial &getMaterial(u32 i);
    const char &getC() const;
    const float &getAdvance() const;

public:
    void OnRegisterSceneNode();
    void render();

private:
    core::aabbox3d<f32> box;
    std::vector<video::S3DVertex> vertexList;
    std::vector<u16> indiceList;
    scene::E_PRIMITIVE_TYPE primitiveType;
    video::SMaterial material;
    const char c;
    const float advance;
};

#endif /* !CHARACTERSCENENODE_HPP */