/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IrrFontBuffer.cpp
*/

#include "Text3d/IrrFontBuffer.hpp"
#include "Error.hpp"

/*
 * Constructors // Desctructors
 */
IrrFontBuffer::IrrFontBuffer(const std::string &fileName, const string &cList) : charSize(200) {
    sf::Font font;

    if (!font.loadFromFile(fileName))
        throw ERROR("IrrFontBuffer");
    for (const char &c : cList)
        irrFontMap[c] = new IrrFont(font, c, charSize);
}

IrrFontBuffer::~IrrFontBuffer() {
    for (auto &it : irrFontMap)
        delete it.second;
}

/*
 * Getters // Setters
 */
const uint &IrrFontBuffer::getCharSize() const {
    return charSize;
}

IrrFont *IrrFontBuffer::getIrrFont(const char &c) {
    return irrFontMap[c];
}

/*
 * Methods
 */
