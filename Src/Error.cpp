/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Error.cpp
*/

#include "Error.hpp"

/*
 * Constructors // Destructors
 */
Error::Error(std::string _message) : message(std::move(_message)) {
}

/*
 * Getters // Setters
 */
const char *Error::what() const noexcept {
    return message.c_str();
}

/*
 * Methods
 */
