/*
** EPITECH PROJECT, 2019
** for_norme
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
    IrrFontBuffer(const std::string &fileName, const std::string &cList);
    ~IrrFontBuffer();
    IrrFont *getIrrFont(const char &c);

private:
    std::map<char, IrrFont*> irrFontMap; // TODO use unique_ptr
};

#endif
