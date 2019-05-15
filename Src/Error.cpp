/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Error.cpp
*/

#include "Error.hpp"

Error::Error(const string &_message)
    : message(_message)
{
}

const char *Error::what() const throw()
{
    return message.c_str();
}
