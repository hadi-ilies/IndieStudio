/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @date © 2019, Zappy group
 * @file
 */

#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <exception>

/**
 * Macro to create an Error (File, function and line are set by default)
 */
#define ERROR(str) Error(str, __FILE__, __FUNCTION__, __LINE__)

class Error : public std::exception {
public:
    explicit Error(std::string what = "unknown", std::string file = "unknown",
                   std::string function = "unknown", size_t line = 0) : _what(
            std::move(what)), _file(std::move(file)), _function(
            std::move(function)), _line(line) {};

public:
    const char *what() const noexcept override {
        return this->_what.c_str();
    }

    const char *where() const {
        static std::string where = this->_file + " : " + this->_function
            + " : " + std::to_string(this->_line);
        return where.c_str();
    }

private:
    const std::string _what;
    const std::string _file;
    const std::string _function;
    const size_t _line;
};

#endif /* !ERROR_HPP */
