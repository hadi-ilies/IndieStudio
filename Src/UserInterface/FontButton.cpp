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
FontButton::FontButton(Window &window, const vector3df &position, const std::string &name, IrrFontBuffer &irrFontBuffer)
    : AButton(window, position, name, "Font")
{
    button = new WordSceneNode(window, name, SColor(255, rand() % 2 * 255, rand() % 2 * 255, rand() % 2 * 255), irrFontBuffer);;
    if (!button)
        throw ERROR("button can not be created");
    button->setPosition(position);
    button->setRotation(vector3df(0, -90, 0)); // TODO set in param
}

FontButton::~FontButton() {
    delete button;
}

/*
 * Getters // Setters
 */

/*
 * Methods
 */
bool FontButton::animation(const vector3df &destPos, const f32 &timestamps) {
    if (!isAnimationFinished())
        return false;
    anim = button->addTranslation(destPos, timestamps);
    return true;
}
