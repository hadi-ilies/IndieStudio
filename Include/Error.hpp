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

class Error : public std::exception {
public:
    explicit Error(std::string what = "unknown", std::string file = "unknown", std::string function = "unknown", int line = 0) : _what(
            std::move(what)), _file(std::move(file)), _function(std::move(function)), _line(line) {};
    ~Error() = default;

public:
    const char *what() const noexcept override {
        return this->_what.c_str();
    }
    const char *where() {
        std::stringstream ss;

        ss << this->_file << " : " << this->_function << " : " << this->_line;
        this->_where = ss.str();
        return this->_where.c_str();
    }

protected:
    std::string _what;
    std::string _where;
    std::string _file;
    std::string _function;
    int _line;
};

#endif /* !ERROR_HPP */
