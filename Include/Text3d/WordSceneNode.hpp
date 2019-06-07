/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** WordSceneNode.hpp
*/

#ifndef WORDSCENENODE_HPP
#define WORDSCENENODE_HPP

#include "CharacterSceneNode.hpp"
#include "IrrFontBuffer.hpp"

class WordSceneNode
{
public:
    WordSceneNode(scene::ISceneManager *smgr, const std::string &_str, IrrFontBuffer &irrFontBuffer);
    void setPosition(const core::vector3df &position);

private:
    const std::string str;
    std::vector<CharacterSceneNode*> characterList; // TODO use unique_ptr
};

#endif
