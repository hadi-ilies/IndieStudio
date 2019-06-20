/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, OOP_indie_studio_2018, Zappy group
 * @package 3D FontGenerator
 * @file CharacterSceneNode
 */

#ifndef CHARACTERSCENENODE_HPP
#define CHARACTERSCENENODE_HPP

#include "IrrFont.hpp"
#include "Window.hpp"

class CharacterSceneNode : public scene::ISceneNode {
public:
    CharacterSceneNode(Window &window, const IrrFont &irrFont, const SColor &color); // TODO add position
    ~CharacterSceneNode();
    const core::aabbox3d<f32> &getBoundingBox() const;
    u32 getMaterialCount() const;
    video::SMaterial &getMaterial(u32 i);
    const char &getC() const;
    const float &getAdvance() const;
    void OnRegisterSceneNode();
    void render();

private:
    u32 getPrimCount() const;

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
