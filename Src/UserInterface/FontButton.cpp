/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** FontButton
*/

#include "Error.hpp"
#include "UserInterface/FontButton.hpp"

FontButton::FontButton(Window *window, const vector3df &position, const std::string &name)
    : AButton(window, position, name, "Font")
{
    if (window) {
        button = window->addText(name);
        if (!button)
            throw Error("button can not be created");
        button->setPosition(position);
    }
}

FontButton::~FontButton()
{
}

bool FontButton::animation(Window *window, const vector3df &destPos, const f32 &timestamps)
{
    if (!animHasFinished())
        return false;
    vector3df test = position;
    for (auto character : button->getCharacterList()) {
        anim = window->createTranslation(test, destPos, timestamps);
        position = destPos;
        if (anim) {
            character->addAnimator(anim);
            anim->drop();
        }
    }
    return true;
}
