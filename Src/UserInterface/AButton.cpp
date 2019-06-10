/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** AButton
*/

#include "UserInterface/AButton.hpp"

/*
 * Constructors // Destructors
 */
AButton::AButton(const vector3df &position, std::string name, std::string type) : position(position), name(std::move(name)), anim(nullptr),
                                                                                  type(std::move(type)) {
}

AButton::~AButton() = default;

/*
 * Getters // Setters
 */
const std::string AButton::getName() const {
    return name;
}

vector3df AButton::getPosition() const {
    return position;
}

bool AButton::isAnimationFinished() const {
    return !anim || anim->hasFinished();
}

/*
 * Methods
 */
