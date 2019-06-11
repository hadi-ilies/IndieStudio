/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** CharacterSceneNode.cpp
*/

#include "Text3d/CharacterSceneNode.hpp"

/*
 * Constructors // Destructors
 */
CharacterSceneNode::CharacterSceneNode(scene::ISceneManager *smgr, const IrrFont &irrFont) : scene::ISceneNode(smgr->getRootSceneNode(),
                                                                                                               smgr, -1), c(irrFont.getC()),
                                                                                             advance(irrFont.getAdvance()) {
    material.Wireframe = false;
    material.Lighting = false;

    for (const core::vector3df &point : irrFont.getPointList())
        vertexList.emplace_back(point, core::vector3df(0, 0, 0), video::SColor(255, 255, 0, 0), core::vector2df(0, 0));
    indiceList = irrFont.getIndiceList();
    primitiveType = irrFont.getPrimitiveType();

    box.reset(vertexList[0].Pos);
    for (s32 i = 1 ; i < vertexList.size() ; i++)
        box.addInternalPoint(vertexList[i].Pos);
}

/*
 * Getters // Setters
 */
const core::aabbox3d<f32> &CharacterSceneNode::getBoundingBox() const {
    return box;
}

u32 CharacterSceneNode::getMaterialCount() const {
    return 1;
}

video::SMaterial &CharacterSceneNode::getMaterial(u32 i) {
    return material;
}

const char &CharacterSceneNode::getC() const {
    return c;
}

const float &CharacterSceneNode::getAdvance() const {
    return advance;
}

/*
 * Methods
 */
void CharacterSceneNode::OnRegisterSceneNode() {
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);
    ISceneNode::OnRegisterSceneNode();
}

void CharacterSceneNode::render() {
    video::IVideoDriver *driver = SceneManager->getVideoDriver();

    driver->setMaterial(material);
    driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
    driver->drawVertexPrimitiveList(vertexList.data(), vertexList.size(), indiceList.data(), indiceList.size(), video::EVT_STANDARD,
                                    primitiveType, video::EIT_16BIT);
}
