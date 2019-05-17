/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Error.cpp
*/

#include "Error.hpp"

Error::Error(const std::string &_message)
    : message(_message)
{
}

const char *Error::what() const throw()
{
    return message.c_str();
}
