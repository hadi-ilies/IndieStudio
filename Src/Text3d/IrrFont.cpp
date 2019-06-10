/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** IrrFont.cpp
*/

#include <iostream> // ?
#include "Text3d/IrrFont.hpp"
#include "Error.hpp"

IrrFont::IrrFont(const sf::Font &font, const char &_c)
    : c(_c)
{
    const uint size = 100;
    const sf::Texture &fontTexture = font.getTexture(size);
    const sf::Glyph &glyph = font.getGlyph(c, size, false);
    advance = glyph.advance;
    sf::Sprite tmpSprite(fontTexture);

    tmpSprite.setTextureRect(glyph.textureRect);
    sf::RenderTexture renderTexture;

    if (!renderTexture.create(tmpSprite.getGlobalBounds().width, tmpSprite.getGlobalBounds().height))
        throw Error("error font");
    renderTexture.clear(sf::Color::Transparent);
    std::cout << "Hello = > " << &renderTexture << std::endl;
    renderTexture.draw(tmpSprite);
    std::cout << "MDR" << std::endl;
    renderTexture.display();
    const sf::Texture &charTexture = renderTexture.getTexture();
    sf::Image image = charTexture.copyToImage();

    for (uint i = 0; i < image.getSize().x; i++)
        for (uint j = 0; j < image.getSize().y; j++) {
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
                pointList.push_back(core::vector3df(i / (size / 2.0), (image.getSize().y - j) / (size / 2.0), 0 / (size / 2.0))); // TODO - size / 2
        }
    for (size_t i = 0; i < pointList.size(); i++)
        indiceList.push_back(i);
    cerr << "pre generate character '" << c << "'" << endl;
}

const char &IrrFont::getC() const
{
    return c;
}

const float &IrrFont::getAdvance() const
{
    return advance;
}

const std::vector<core::vector3df> &IrrFont::getPointList() const
{
    return pointList;
}

const std::vector<u16> &IrrFont::getIndiceList() const
{
    return indiceList;
}
