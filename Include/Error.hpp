/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Error.hpp
*/

#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <exception>
#include <utility>

using namespace std;

class Error : public exception {
public:
    Error(std::string _message);

public:
    const char *what() const noexcept override;

private:
    const std::string message;
};

#endif /* !ERROR_HPP */