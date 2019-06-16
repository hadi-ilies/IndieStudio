/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Button.cpp
*/

#include "UserInterface/Button.hpp"
#include "Error.hpp"

/*
 * Constructors // Destructors
 */
Button::Button(Window &_window, const vector3df &position, const std::string &name, const std::string &model,
               const std::string &texture) : AButton(_window, position, name, "Model"), model(model), texture(texture) {
    button = window.addAnimatedMesh((std::string) "Resources/Entity/" + model + "/Model/Idle.md2",
                                    (std::string) "Resources/Entity/" + model + "/Texture/" + texture + ".png");
    if (!button)
        throw ERROR("button can not be created");
    button->setPosition(position);
}

Button::~Button() {
    if (button)
        button->remove();
}

/*
 * Getters // Setters
 */
const std::string Button::getTexture() const {
    return texture;
}

const std::string Button::getModel() const {
    return model;
}

/*
 * Methods
 */
bool Button::animation(const vector3df &destPos, const f32 &timestamps) {
    if (!isAnimationFinished())
        return false;
    anim = window.createTranslation(position, destPos, (const u32) timestamps);
    position = destPos;
    if (anim) {
        button->addAnimator(anim);
        anim->drop();
    }
    return true;
}
