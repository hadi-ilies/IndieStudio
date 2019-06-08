/*
** EPITECH PROJECT, 2019
** Button
** File description:
** Button
*/

#include "Error.hpp"
#include "UserInterface/Button.hpp"

Button::Button(Window *window, const vector3df &position, const std::string &name, const std::string &model, const std::string &texture)
    : AButton(window, position, name, "Model"), model(model), texture(texture)
{
    if (window) {
        button = window->addAnimatedMesh((std::string) "Resources/Entity/" + model + "/Model/Idle.md2", (std::string) "Resources/Entity/" + model + "/Texture/" + texture + ".png");
        if (!button)
            throw Error("button can not be created");
        button->setPosition(position);
    }
}

Button::~Button()
{
}

const std::string Button::getTexture() const
{
    return texture;
}

const std::string Button::getModel() const
{
    return model;
}

#include <iostream> //tmp
//anim in loop for text in WordSceneNode
bool Button::animation(Window *window, const vector3df &destPos, const f32 &timestamps)
{
    if (!animHasFinished())
        return false;
    anim = window->createTranslation(position, destPos, timestamps);
    position = destPos;
    if (anim) {
        button->addAnimator(anim);
        anim->drop();
    }
    return true;
}
