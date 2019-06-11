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
Error::Error(std::string _message, std::string _source) {
    _message = std::move(_message);
    _source = std::move(_source);
}

/*
 * Getters // Setters
 */

/*
 * Methods
 */
const char *Error::what() const noexcept {
    return message.c_str();
}

const char *Error::where() const noexcept {
    return source.c_str();
}