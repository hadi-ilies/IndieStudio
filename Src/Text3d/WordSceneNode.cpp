/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** WordSceneNode.cpp
*/

#include "Text3d/WordSceneNode.hpp"

WordSceneNode::WordSceneNode(scene::ISceneManager *smgr, const std::string &_str, IrrFontBuffer &irrFontBuffer)
    : str(_str)
{
    for (size_t i = 0; i < str.size(); i++)
        characterList.push_back(new CharacterSceneNode(smgr, *irrFontBuffer.getIrrFont(str[i])));
    setPosition(core::vector3df(0, 0, 0));
}

 std::vector<CharacterSceneNode*> WordSceneNode::getCharacterList() const
{
    return characterList;
}

void WordSceneNode::setPosition(const core::vector3df &position)
{
    core::vector3df pos = position;

    for (auto &character : characterList) {
        character->setPosition(pos);
        pos.X += character->getAdvance() / 50.0; // TODO replace /50.0 with ...
    }
}
