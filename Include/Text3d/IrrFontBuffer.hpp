/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** IrrFontBuffer.hpp
*/

#ifndef IRRFONTBUFFER_HPP
#define IRRFONTBUFFER_HPP

#include <iostream> // tmp
#include "IrrFont.hpp"

class IrrFontBuffer
{
public:
    explicit IrrFontBuffer(const std::string &fileName, const std::string &cList = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    ~IrrFontBuffer();
    IrrFont *getIrrFont(const char &c);

private:
    std::map<char, IrrFont*> irrFontMap; // TODO use unique_ptr
};

#endif /* !IRRFONTBUFFER_HPP */
