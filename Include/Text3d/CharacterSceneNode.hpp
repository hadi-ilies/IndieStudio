/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** CharacterSceneNode.hpp
*/

#ifndef CHARACTERSCENENODE_HPP
#define CHARACTERSCENENODE_HPP

#include "IrrFont.hpp"

class CharacterSceneNode : public scene::ISceneNode
{
public:
    CharacterSceneNode(scene::ISceneManager *smgr, const IrrFont &irrFont); // TODO add position
    void OnRegisterSceneNode();
    void render();
    const core::aabbox3d<f32> &getBoundingBox() const;
    u32 getMaterialCount() const;
    video::SMaterial &getMaterial(u32 i);
    const char &getC() const;
    const float &getAdvance() const;

private:
    core::aabbox3d<f32> box;
    std::vector<video::S3DVertex> vertexList;
    video::SMaterial material;
    const char c;
    const float advance;
};

#endif
