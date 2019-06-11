/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** IrrFontBuffer.cpp
*/

#include "Text3d/IrrFontBuffer.hpp"
#include "Error.hpp"

/*
 * Constructors // Destructors
 */
IrrFontBuffer::IrrFontBuffer(const std::string &fileName, const string &cList) {
    sf::Font font;

    if (!font.loadFromFile(fileName))
        throw ERROR("IrrFontBuffer error");
    for (const char &c : cList)
        irrFontMap[c] = new IrrFont(font, c); // TODO not insert if IrrFont is NULL or IrrFont throw
}

IrrFontBuffer::~IrrFontBuffer() {
    for (auto &it : irrFontMap)
        delete it.second;
}

/*
 * Getters // Setters
 */
IrrFont *IrrFontBuffer::getIrrFont(const char &c) {
    // TODO throw
    return irrFontMap[c];
}

/*
 * Methods
 */
