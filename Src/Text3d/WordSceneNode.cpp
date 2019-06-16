/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** WordSceneNode.cpp
*/

#include "Text3d/WordSceneNode.hpp"

/*
 * Constructors // Destructors
 */
WordSceneNode::WordSceneNode(Window &_window, std::string _str, const SColor &color, IrrFontBuffer &irrFontBuffer)
    : window(_window), str(std::move(_str)), charSize(irrFontBuffer.getCharSize())
{
    SColor newColor = color;

    for (char i : str) {
        newColor.setRed(newColor.getRed() / 1.2);
        newColor.setGreen(newColor.getGreen() / 1.2);
        newColor.setBlue(newColor.getBlue() / 1.2);
        characterList.push_back(new CharacterSceneNode(window, *irrFontBuffer.getIrrFont(i), newColor));
    }
    setPosition(core::vector3df(0, 0, 0));
}


WordSceneNode::~WordSceneNode()
{
    for (auto &it : characterList)
        delete it;
}

/*
 * Getters // Setters
 */
void WordSceneNode::setPosition(const core::vector3df &position)
{
    core::vector3df pos = position;

    pos.Z -= getWorldSize() / 2.0;
    for (auto &character : characterList) {
        character->setPosition(pos);
        pos.Z += character->getAdvance() / (float)charSize;
    }
}

void WordSceneNode::setRotation(const core::vector3df &rotation)
{
    for (auto &character : characterList)
        character->setRotation(rotation);
}

/*
 * Methods
 */
scene::ISceneNodeAnimator *WordSceneNode::addTranslation(const core::vector3df &destPos, const u32 &timestamp)
{
    scene::ISceneNodeAnimator *anim = nullptr;
    core::vector3df pos = destPos;

    pos.Z -= getWorldSize() / 2.0;
    for (auto &character : characterList) {
        const core::vector3df initPos = character->getPosition();

        anim = window.createTranslation(initPos, pos, timestamp);
        if (anim) {
            character->addAnimator(anim);
            anim->drop();
        }
        pos.Z += character->getAdvance() / (float) charSize;
    }
    return anim;
}

const float WordSceneNode::getWorldSize() const
{
    float worldSize = 0;

    for (auto &character : characterList)
        worldSize += character->getAdvance() / (float)charSize;
    return worldSize;
}
