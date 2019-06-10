/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ButtonElement
*//*


#include "UserInterface/ButtonElement.hpp"

*/
/*
 * Contructors // Destructors
 *//*

ButtonElement::ButtonElement(const vector3df &position, const std::string &name, const std::string &model, const std::string &texture)
        : MenuElement(position, "Button"), button(new Button(position, name, model, texture)) {
}

ButtonElement::~ButtonElement() = default;

*/
/*
 * Getters // Setters
 *//*

Button *ButtonElement::getButton() const {
    return button;
}

*/
/*
 * Methods
 */
