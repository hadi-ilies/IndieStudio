/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Error.hpp
*/

#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <exception>

using namespace std;

class Error : public exception
{
public:
    Error(const std::string &_message);
    const char *what() const throw();

private:
    const std::string message;
};

#endif
