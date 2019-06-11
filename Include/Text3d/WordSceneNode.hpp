/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** WordSceneNode.hpp
*/

#ifndef WORDSCENENODE_HPP
#define WORDSCENENODE_HPP

#include <utility>

#include "CharacterSceneNode.hpp"
#include "IrrFontBuffer.hpp"

class WordSceneNode {
public:
    WordSceneNode(scene::ISceneManager *smgr, std::string _str, IrrFontBuffer &irrFontBuffer);
    void setPosition(const core::vector3df &position);
    void setRotation(const core::vector3df &rotation);
    scene::ISceneNodeAnimator *addTranslation(const core::vector3df &destPos, const u32 &timestamp);

private:
    const std::string str;
    std::vector<CharacterSceneNode*> characterList; // TODO use unique_ptr
};

#endif /* !WORDSCENENODE_HPP */
