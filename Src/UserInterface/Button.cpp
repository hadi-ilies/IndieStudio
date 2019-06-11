/*
** EPITECH PROJECT, 2019
** Button
** File description:
** Button
*/

#include "UserInterface/Button.hpp"
#include "Error.hpp"

/*
 * Constructors // Destructors
 */
Button::Button(const vector3df &position, const std::string &name, const std::string &model, const std::string &texture) : AButton(position,
                                                                                                                                   name,
                                                                                                                                   "Model"),
                                                                                                                           model(model),
                                                                                                                           texture(texture) {
    button = Window::getInstance().addAnimatedMesh((std::string) "Resources/Entity/" + model + "/Model/Idle.md2",
                                                   (std::string) "Resources/Entity/" + model + "/Texture/" + texture + ".png");
    if (!button)
        throw ERROR("button can not be created");
    button->setPosition(position);
}

Button::~Button() = default;

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
    anim = Window::getInstance().createTranslation(position, destPos, timestamps);
    position = destPos;
    if (anim) {
        button->addAnimator(anim);
        anim->drop();
    }
    return true;
}
