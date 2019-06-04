/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** RandomMapGenerator.hpp
*/

#ifndef BOMBERMAN_RANDOMMAPGENERATOR_HPP
#define BOMBERMAN_RANDOMMAPGENERATOR_HPP

#include <fstream>

#include "Block.hpp"

namespace RandomMapGenerator {
    class isValidPosition {
    public:
        isValidPosition(const vector3du& vectorSize, int randomPosX, int randomPosY);
        ~isValidPosition();

    public:
        bool isValidOneP();
        bool isValidTwoP();
        bool isValidThreeP();
        bool isValidFourP();

    private:
        vector3du size;
        int posX;
        int posZ;
    };

    class Generator {
    public:
        explicit Generator(const std::string &_fileName, int nbPlayer, const vector3du& _size); // TODO
        ~Generator();

    public:
        void generate(float fillPercentage);

    private:
        void create(const vector3du &_size);
        bool addBlock(const vector3du &pos, const std::string &type);
        bool save();
        bool isValidPosition(int randomPosX, int randomPosZ);

    protected:
        std::string fileName;
        vector3du size;
        Block ****tab;
        int nbPlayer;
    };
}




#endif /* !BOMBERMAN_RANDOMMAPGENERATOR_HPP */
