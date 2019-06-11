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
    std::string source;
};

#endif /* !ERROR_HPP */

/*
 * public:
    Error(std::string const &message, std::string const &source);

public:
    const char *what() const noexcept;
    const char *where() const noexcept;

protected:
    std::string message;
    std::string source;
 */