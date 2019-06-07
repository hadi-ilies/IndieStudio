/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** IrrFontBuffer.cpp
*/

#include "Text3d/IrrFontBuffer.hpp"
#include "Error.hpp"

IrrFontBuffer::IrrFontBuffer(const std::string &fileName, const string &cList)
{
    sf::Font font;

    if (!font.loadFromFile(fileName))
        ; // TODO throw
    for (const char &c : cList)
        irrFontMap[c] = new IrrFont(font, c); // TODO not insert if IrrFont is NULL or IrrFont throw
}

IrrFontBuffer::~IrrFontBuffer()
{
    for (auto it = irrFontMap.begin(); it != irrFontMap.end(); it++)
        delete it->second;
}

IrrFont *IrrFontBuffer::getIrrFont(const char &c)
{
    // TODO throw
    return irrFontMap[c];
}
