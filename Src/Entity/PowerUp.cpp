/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** PowerUp.cpp
*/

#include "Entity/PowerUp.hpp"

/*
 * Constructors // Destructors
 */
PowerUp::PowerUp(std::string _type, World *world, const vector3du &position) : Entity(_type, world, position), type(std::move(_type)) {

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