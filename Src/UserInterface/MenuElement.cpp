/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** UserInterface
*/

#include "UserInterface/MenuElement.hpp"

/*
 * Constructors // Destructors
 */
MenuElement::MenuElement(const vector3df &position, std::string type) : position(position), type(std::move(type)) {

}

MenuElement::~MenuElement() = default;

/*
 * Getters // Setters
 */
vector3df MenuElement::getPosition() const {
    return position;
}

std::string MenuElement::getType() const {
    return type;
}

/*
 * Methods
 */
