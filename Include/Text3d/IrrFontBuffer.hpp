/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, OOP_indie_studio_2018, Zappy group
 * @package 3D FontGenerator
 * @file IrrFontBuffer
 */

#ifndef IRRFONTBUFFER_HPP
#define IRRFONTBUFFER_HPP

#include "IrrFont.hpp"

class IrrFontBuffer {
public:
    explicit IrrFontBuffer(const std::string &fileName, const std::string &cList = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    ~IrrFontBuffer();
    const uint &getCharSize() const;
    IrrFont *getIrrFont(const char &c);

private:
    const uint charSize;
    std::map<char, IrrFont*> irrFontMap; // TODO use unique_ptr
};

#endif /* !IRRFONTBUFFER_HPP */
