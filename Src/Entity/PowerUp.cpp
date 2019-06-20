/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** PowerUp.cpp
*/

#include "Entity/PowerUp.hpp"

/*
 * Constructors // Destructors
 */
PowerUp::PowerUp(Window *window, std::string _type, World *world, const vector3du &position) : Entity(
        window, _type, world, position), type(std::move(_type)) {

}

PowerUp::~PowerUp() = default;

/*
 * Getters // Setters
 */
const std::string &PowerUp::getType() const {
    return type;
}

/*
 * Methods
 */