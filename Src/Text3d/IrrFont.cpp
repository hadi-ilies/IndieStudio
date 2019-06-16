/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IrrFont.cpp
*/

#include "Text3d/IrrFont.hpp"
#include "Error.hpp"

/*
 * Constructors // Destructors
 */
IrrFont::IrrFont(const sf::Font &font, const char &_c, const uint &size) : c(_c) {
    const sf::Texture &fontTexture = font.getTexture(size);
    const sf::Glyph &glyph = font.getGlyph(c, size, false);
    advance = glyph.advance;
    sf::Sprite tmpSprite(fontTexture);

    tmpSprite.setTextureRect(glyph.textureRect);
    sf::RenderTexture renderTexture;

    if (!renderTexture.create(tmpSprite.getGlobalBounds().width, tmpSprite.getGlobalBounds().height))
        throw ERROR("renderTexture can't be create");
    renderTexture.clear(sf::Color::Transparent);
    renderTexture.draw(tmpSprite);
    renderTexture.display();
    const sf::Texture &charTexture = renderTexture.getTexture();
    sf::Image image = charTexture.copyToImage();

    for (uint i = 0 ; i < image.getSize().x ; i++)
        for (uint j = 0 ; j < image.getSize().y ; j++) {
            bool bord = false;

            if (image.getPixel(i, j).a < 100)
                continue;
            if (i == 0 || image.getPixel(i - 1, j).a < 100)
                bord = true;
            else if (j == 0 || image.getPixel(i, j - 1).a < 100)
                bord = true;
            else if (i == image.getSize().x - 1 || image.getPixel(i + 1, j).a < 100)
                bord = true;
            else if (j == image.getSize().y - 1 || image.getPixel(i, j + 1).a < 100)
                bord = true;
            if (bord)
                for (uint n = 0 ; n < 20 ; n++)
                    pointList.emplace_back(i / (float) size, (image.getSize().y - j) / (float) size, n / 100.0);
            pointList.emplace_back(i / (float) size, (image.getSize().y - j) / (float) size,
                                                0 / (float) size); // TODO - size / 2
        }
    for (size_t i = 0 ; i < pointList.size() ; i++)
        indiceList.push_back(i);
    primitiveType = scene::EPT_POINTS; // TODO use EPT_QUADS
}

/*
 * Getters // Setters
 */
const char &IrrFont::getC() const {
    return c;
}

const float &IrrFont::getAdvance() const {
    return advance;
}

const std::vector<core::vector3df> &IrrFont::getPointList() const {
    return pointList;
}

const std::vector<u16> &IrrFont::getIndiceList() const {
    return indiceList;
}

const scene::E_PRIMITIVE_TYPE &IrrFont::getPrimitiveType() const {
    return primitiveType;
}

/*
 * Methods
 */