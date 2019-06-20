/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** CharacterSceneNode.cpp
*/

#include "Text3d/CharacterSceneNode.hpp"

/*
 * Constructors // Destructors
 */
CharacterSceneNode::CharacterSceneNode(Window &window, const IrrFont &irrFont, const SColor &color)
        : scene::ISceneNode(window.getSmgr()->getRootSceneNode(), window.getSmgr(), -1),
          c(irrFont.getC()), advance(irrFont.getAdvance()) {
    //const video::SColor color(255, rand() % 256, rand() % 256, rand() % 256);
    material.Wireframe = false;
    material.Lighting = false;

    for (const core::vector3df &point : irrFont.getPointList())
        vertexList.emplace_back(point, core::vector3df(0, 0, 0), color, core::vector2df(0, 0));
    indiceList = irrFont.getIndiceList();
    primitiveType = irrFont.getPrimitiveType();

    box.reset(vertexList[0].Pos);
    for (s32 i = 1 ; i < vertexList.size() ; i++)
        box.addInternalPoint(vertexList[i].Pos);
}

CharacterSceneNode::~CharacterSceneNode() {
    remove();
}

/*
 * Getters // Setters
 */
const core::aabbox3d <f32> &CharacterSceneNode::getBoundingBox() const {
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
    driver->drawVertexPrimitiveList(vertexList.data(), vertexList.size(), indiceList.data(),
                                    getPrimCount(), video::EVT_STANDARD, primitiveType,
                                    video::EIT_16BIT);
}

u32 CharacterSceneNode::getPrimCount() const {
    if (primitiveType == scene::EPT_POINTS)
        return indiceList.size();
    else if (primitiveType == scene::EPT_LINES)
        return indiceList.size() / 2;
    else if (primitiveType == scene::EPT_QUADS)
        return indiceList.size() / 4;
    else
        return indiceList.size();
}
