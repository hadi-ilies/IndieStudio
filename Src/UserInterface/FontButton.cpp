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
        throw Error("button can not be created", "FontButton");
    button->setPosition(position);
}

FontButton::~FontButton() = default;

/*
 * Getters // Setters
 */

/*
 * Methods
 */
bool FontButton::animation(const vector3df &destPos, const f32 &timestamps) {
    if (!isAnimationFinished())
        return false;
    vector3df test = position;
    vector3df destTest = destPos;
    for (auto character : button->getCharacterList()) {
        anim = Window::getInstance().createTranslation(test, destTest, timestamps);
        position = destPos;
        destTest.X += 1.50;
        if (anim) {
            character->addAnimator(anim);
            anim->drop();
        }
    }
    return true;
}
