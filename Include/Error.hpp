#include <utility>

#include <utility>

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

#include <string>
#include <sstream>

class Error : public std::exception // TODO move in cpp
{
public:
    explicit Error(std::string what = "unknown", std::string file = "unknown", std::string function = "unknown", size_t line = 0)
        : _what(std::move(what)), _file(std::move(file)), _function(std::move(function)), _line(line) {};
    ~Error() = default;

public:
    const char *what() const noexcept override
        {
            return this->_what.c_str();
        }
    const char *where()
        {
            std::string where = this->_file + " : " + this->_function + " : " + to_string(this->_line);

            return where.c_str();
        }

protected:
    const std::string _what;
    const std::string _file;
    const std::string _function;
    const size_t _line;
};

#endif /* !ERROR_HPP */
