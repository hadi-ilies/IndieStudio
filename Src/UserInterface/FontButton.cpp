/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** FontButton
*/

#include "UserInterface/FontButton.hpp"
#include "Error.hpp"

/*
 * Constructors // Destructors
 */
FontButton::FontButton(const vector3df &position, const std::string &name) : AButton(position, name, "Font") {
    button = Window::getInstance().addText(name);
    if (!button)
        throw ERROR("button can not be created");
    button->setPosition(position);
    button->setRotation(vector3df(0, -90, 0)); // TODO set in param
}

FontButton::~FontButton() = default;

/*
 * Getters // Setters
 */

/*
 * Methods
 */
bool FontButton::animation(const vector3df &destPos, const f32 &timestamps)
{
    if (!isAnimationFinished())
        return false;
    anim = button->addTranslation(destPos, timestamps);
    return true;
}
