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
    Error(std::string _message, std::string _source);

public:
    const char *what() const noexcept override;
    const char *where() const noexcept;

private:
    const std::string message;
    const std::string source;
};

class ErrorClient : public Error {
public:
    explicit ErrorClient(std::string _message);
};

class ErrorServer : public Error {
public:
    explicit ErrorServer(std::string _message);
};

#endif /* !ERROR_HPP */
