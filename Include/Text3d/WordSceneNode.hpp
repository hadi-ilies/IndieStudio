/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @date © 2019, Zappy group
 * @package 3D FontGenerator
 * @file WordSceneNode
 */

#ifndef WORDSCENENODE_HPP
#define WORDSCENENODE_HPP

#include <utility>

#include "CharacterSceneNode.hpp"
#include "IrrFontBuffer.hpp"
#include "Window.hpp"

class WordSceneNode {
public:
    WordSceneNode(Window &_window, std::string _str, const SColor &color, IrrFontBuffer &irrFontBuffer);
    ~WordSceneNode();
    void setPosition(const core::vector3df &position);
    void setRotation(const core::vector3df &rotation);
    scene::ISceneNodeAnimator *addTranslation(const core::vector3df &destPos, const u32 &timestamp);

private:
    const float getWorldSize() const;

private:
    Window &window;
    const std::string str;
    const uint charSize;
    std::vector<CharacterSceneNode *> characterList; // TODO use unique_ptr
};

#endif /* !WORDSCENENODE_HPP */
