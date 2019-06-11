/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** WordSceneNode.cpp
*/

#include "Text3d/WordSceneNode.hpp"
#include "Window.hpp" // ?

WordSceneNode::WordSceneNode(scene::ISceneManager *smgr, std::string _str, IrrFontBuffer &irrFontBuffer)
    : str(std::move(_str))
{
    for (char i : str)
        characterList.push_back(new CharacterSceneNode(smgr, *irrFontBuffer.getIrrFont(i)));
    setPosition(core::vector3df(0, 0, 0));
}

void WordSceneNode::setPosition(const core::vector3df &position)
{
    core::vector3df pos = position;

    for (auto &character : characterList) {
        character->setPosition(pos);
        pos.Z += character->getAdvance() / 50.0; // TODO replace "/ 50.0" with ...
    }
}

void WordSceneNode::setRotation(const core::vector3df &rotation)
{
    for (auto &character : characterList)
        character->setRotation(rotation);
}

scene::ISceneNodeAnimator *WordSceneNode::addTranslation(const core::vector3df &destPos, const u32 &timestamp)
{
    scene::ISceneNodeAnimator *anim = NULL;
    core::vector3df pos = destPos;

    for (auto &character : characterList) {
        const core::vector3df initPos = character->getPosition();

        anim = Window::getInstance().createTranslation(initPos, pos, timestamp);
        if (anim) {
            character->addAnimator(anim);
            anim->drop();
        }
        pos.Z += character->getAdvance() / 50.0; // TODO replace "/ 50.0" with ...
    }
    return anim;
}
