/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** RandomMapGenerator.hpp
*/

#include <iostream>
#include "RandomMapGenerator.hpp"

/*
 *   Constructors // Destructors
 */
RandomMapGenerator::Generator::Generator(const std::string &_fileName, int _nbPlayer, const vector3du &_size) {
    this->fileName = _fileName;
    this->nbPlayer = _nbPlayer;
    this->size = _size;
}

RandomMapGenerator::Generator::~Generator() = default;

/*
 *   Getters // Setters
 */

/*
 *   Methods
 */
void RandomMapGenerator::Generator::generate(float fillPercentage) {
    float nbBox;
    float maxBlock;
    int nbCube = 0;
    int randomPosX = 0;
    int randomPosZ = 0;
    srand((time(0)));

    create(size);
    for (uint i = 0 ; i < size.X ; i++) // tmp
        for (uint j = 0 ; j < size.Z ; j++) {
            addBlock(vector3du(i, 0, j), "Ground");
            if (i == 0 || j == 0 || i == size.X - 1 || j == size.Z - 1)
                addBlock(vector3du(i, 1, j), "Ground");
            else if (((i + 1) * (j + 1)) % 2) {
                addBlock(vector3du(i, 1, j), "Wall");
                nbCube++;
            }
        }
    maxBlock = (size.X * size.Z) - nbCube;
    nbBox = maxBlock;

    while (100 - ((nbBox / maxBlock) * 100) < fillPercentage) {
        randomPosX = rand() % 20 + 1;
        randomPosZ = rand() % 20 + 1;
        if (isValidPosition(randomPosX, randomPosZ))
            if (addBlock(vector3du(randomPosX, 1, randomPosZ), "Box"))
            nbBox--;
    }
    this->save();
}

bool RandomMapGenerator::Generator::isValidPosition(int randomPosX, int randomPosZ) {

    RandomMapGenerator::isValidPosition validator(this->size, randomPosX, randomPosZ);

    switch (this->nbPlayer) {
        case 1:
            return validator.isValidOneP();
        case 2:
            return validator.isValidOneP() && validator.isValidTwoP();
        case 3:
            return validator.isValidOneP() && validator.isValidTwoP() && validator.isValidThreeP();
        case 4:
            return validator.isValidOneP() && validator.isValidTwoP() && validator.isValidThreeP() && validator.isValidFourP();
        default:
            return true;
    }
}

void RandomMapGenerator::Generator::create(const vector3du &_size) {
    size = _size;
    tab = new Block ***[size.X];
    for (uint i = 0 ; i < size.X ; i++) {
        tab[i] = new Block **[size.Y];
        for (uint j = 0 ; j < size.Y ; j++) {
            tab[i][j] = new Block *[size.Z];
            for (uint k = 0 ; k < size.Z ; k++)
                tab[i][j][k] = nullptr;
        }
    }
}

bool RandomMapGenerator::Generator::addBlock(const vector3du &pos, const std::string &type) {
    if (tab[pos.X][pos.Y][pos.Z])
        return false;
    tab[pos.X][pos.Y][pos.Z] = new Block(type);
    return true;
}


bool RandomMapGenerator::Generator::save() {
    ofstream file(this->fileName, ifstream::binary | ifstream::trunc);

    file.write((char *) &size, sizeof(size));

    for (uint i = 0 ; i < size.X ; i++) {
        for (uint j = 0 ; j < size.Y ; j++) {
            for (uint k = 0 ; k < size.Z ; k++) {
                if (!tab[i][j][k])
                    file.write("\0", 1);
                else {
                    // can also work with data
                    file.write(tab[i][j][k]->getType().c_str(), sizeof(char) * (tab[i][j][k]->getType().size()) + 1);
                }
            }
        }
    }
    return true;
}

/*
 * isValidPosition class
 */
/*
 *   Constructors // Destructors
 */
RandomMapGenerator::isValidPosition::isValidPosition(const vector3du &vectorSize, int randomPosX, int randomPosY) {
    this->size = vectorSize;
    this->posX = randomPosX;
    this->posZ = randomPosY;
}

RandomMapGenerator::isValidPosition::~isValidPosition() = default;

/*
 *   Getters // Setters
 */

/*
 *   Methods
 */
bool RandomMapGenerator::isValidPosition::isValidOneP() {
    return !((posX == 1 && posZ == 1) || (posX == 2 && posZ == 1)
            || (posX == 1 && posZ == 2));
}

bool RandomMapGenerator::isValidPosition::isValidTwoP() {
    return !((posX == size.X - 2 && posZ == size.Z - 2)
            || (posX == size.X - 2 && posZ == size.Z - 3)
            || (posX == size.X - 3 && posZ == size.Z - 2));
}

bool RandomMapGenerator::isValidPosition::isValidThreeP() {
    return !((posX == 1 && posZ == size.Z - 2) || (posX == 1 && posZ == size.Z - 3)
            || (posX == 2 && posZ == size.Z - 2));
}

bool RandomMapGenerator::isValidPosition::isValidFourP() {
    return !((posX == size.X - 2 && posZ == 1) || (posX == size.X - 3 && posZ == 1)
            || (posX == size.X - 2 && posZ == 2));
}

