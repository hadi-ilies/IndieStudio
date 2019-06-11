/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** WordSceneNode.cpp
*/

#include "Text3d/WordSceneNode.hpp"

/*
 * Constructors // Destructors
 */
WordSceneNode::WordSceneNode(scene::ISceneManager *smgr, std::string _str, IrrFontBuffer &irrFontBuffer) : str(std::move(_str)) {
    for (char i : str)
        characterList.push_back(new CharacterSceneNode(smgr, *irrFontBuffer.getIrrFont(i)));
    setPosition(core::vector3df(0, 0, 0));
}

/*
 * Getters // Setters
 */
void WordSceneNode::setPosition(const core::vector3df &position) {
    core::vector3df pos = position;

    for (auto &character : characterList) {
        character->setPosition(pos);
        pos.X += character->getAdvance() / 50.0; // TODO replace /50.0 with ...
    }
}

std::vector<CharacterSceneNode *> WordSceneNode::getCharacterList() {
    return characterList;
}

/*void WordSceneNode::setRotation(const core::vector3df &rotation)
{
    // TODO
}
*/
/*
 * Methods
 */
/*
void WordSceneNode::addAnimator(scene::ISceneNodeAnimator *animator)
{
    for (auto &character : characterList) { // TODO
        character->addAnimator(animator);
    }
    }
*/