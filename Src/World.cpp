/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** World.cpp
*/

#include "World.hpp"
#include "Error.hpp"

/*
 * Constructors // Destructors
 */
/**
 * Constructor used to create a world from a random generated map
 * @param _window
 * @param _size
 * @param seed
 */
World::World(Window *_window, const vector3du &_size, const uint &seed) : window(_window), size(_size) {
    if (!generate(size, seed))
        throw ERROR("Generation world failed");
}

/**
 * Constructor used to create a world loaded from a map from a file
 * @param _window
 * @param _fileName
 */
World::World(Window *_window, const std::string &_fileName) : window(_window) {
    if (!load(_fileName))
        throw ERROR("Load world failed");
}

World::~World() {
    for (uint i = 0 ; i < size.X ; i++) {
        for (uint j = 0 ; j < size.Y ; j++) {
            for (uint k = 0 ; k < size.Z ; k++)
                removeBlock(vector3du(i, j, k));
            delete[] tab[i][j];
        }
        delete[] tab[i];
    }
    delete[] tab;
}

/*
 * Getters // Setters
 */
const vector3du &World::getSize() const {
    return size;
}

const Block *World::getBlock(const vector3du &pos) const {
    return tab[pos.X][pos.Y][pos.Z];
}

/*
 * Methods
 */
/**
 * Make the bomb explosion
 * @todo Add 3D explosion
 * @param pos
 * @param power
 */
void World::explode(const vector3du &pos, const uint &power) {
    vector <vector3du> dirList = {
            vector3du(-1, 0, 0), vector3du(1, 0, 0), vector3du(0, 0, -1), vector3du(0, 0, 1),
            vector3du(0, -1, 0),
            vector3du(0, 1, 0),
    };

    for (uint i = 0 ; i <= power ; i++)
        for (auto &j : dirList) {
            const vector3du newPos = pos + j * i;

            if (newPos.X >= size.X || newPos.Y >= size.Y || newPos.Z >= size.Z)
                continue;
            if (tab[newPos.X][newPos.Y][newPos.Z] && tab[newPos.X][newPos.Y][newPos.Z]->getOpaque()) {
                if (tab[newPos.X][newPos.Y][newPos.Z]->getDestructible())
                    removeBlock(newPos);
                j = vector3du(0, 0, 0);
            }
            if (tab[newPos.X][newPos.Y][newPos.Z]
                && tab[newPos.X][newPos.Y][newPos.Z]->getType() == "Fire")
                removeBlock(newPos);
            if (!tab[newPos.X][newPos.Y][newPos.Z])
                addBlock(newPos, "Fire");
        }
}

/**
 * Map generator
 * @todo Add 3D
 * @param _size
 * @param seed
 * @return
 */
bool World::generate(const vector3du &_size, const uint &seed) {
    float nbBox;
    float maxBlock;
    int nbCube = 0;
    int randomPosX;
    int randomPosY;
    int randomPosZ;
    float fillPercentage;
    srand(seed);

    if (size.X < 3 || size.Y < 2 || size.Z < 3)
        return false;

    fillPercentage = rand() % (50 - 25 + 1) + 25;
    create(size);
    for (uint i = 0 ; i < size.X ; i++)
        for (uint j = 0 ; j < size.Z ; j++) {
            addBlock(vector3du(i, 0, j), "Ground");
            if (i == 0 || j == 0 || i == size.X - 1 || j == size.Z - 1)
                addBlock(vector3du(i, 1, j), "Ground");
            else if (((i + 1) * (j + 1)) % 2) {
                addBlock(vector3du(i, 1, j), "Wall");
                nbCube++;
            }
        }
    maxBlock = ((size.X - 1) * (size.Y - 1) * (size.Z - 1)) - nbCube;
    nbBox = maxBlock;

    while (100 - ((nbBox / maxBlock) * 100) < fillPercentage) {
        randomPosX = rand() % (size.X - 1) + 1;
        randomPosY = rand() % (size.Y - 1) + 1;
        randomPosZ = rand() % (size.Z - 1) + 1;
        if (isValidPosition(randomPosX, randomPosZ))
            if (addBlock(vector3du(randomPosX, randomPosY, randomPosZ), "Box"))
                nbBox--;
    }
    return true;
}

/**
 * Load a map from a file
 * @param _fileName (File path)
 * @return
 */
bool World::load(const std::string &_fileName) {
    ifstream file(_fileName, ifstream::binary);
    std::string type;

    if (!file.is_open())
        return false;

    file.read((char *) &size, sizeof(size));

    create(size);
    for (uint i = 0 ; i < size.X ; i++) {
        for (uint j = 0 ; j < size.Y ; j++) {
            for (uint k = 0 ; k < size.Z ; k++) {
                type = "";
                for (char c ; file.read(&c, sizeof(char)) && c ; type += c);
                if (!type.empty())
                    addBlock(vector3du(i, j, k), type);
            }
        }
    }
    return true;
}

/**
 * Save a map in a file
 * @param _fileName (File path)
 * @return
 */
bool World::save(const std::string &_fileName) {
    ofstream file(_fileName, ifstream::binary | ifstream::trunc);

    file.write((char *) &size, sizeof(size));

    for (uint i = 0 ; i < size.X ; i++) {
        for (uint j = 0 ; j < size.Y ; j++) {
            for (uint k = 0 ; k < size.Z ; k++) {
                if (!tab[i][j][k])
                    file.write("\0", 1);
                else {
                    /// @remark Can also work with data() instead of c_str()
                    file.write(tab[i][j][k]->getType().c_str(),
                               sizeof(char) * (tab[i][j][k]->getType().size()) + 1);
                }
            }
        }
    }
    return true;
}

/**
 * Update the map (remove a block if necessary)
 */
void World::update() {
    for (uint i = 0 ; i < size.X ; i++)
        for (uint j = 0 ; j < size.Y ; j++)
            for (uint k = 0 ; k < size.Z ; k++)
                if (tab[i][j][k]) {
                    tab[i][j][k]->update();
                    if (!tab[i][j][k]->getLifeTime())
                        removeBlock(vector3du(i, j, k));
                }
}

/**
 * Initialize a map
 * @param _size
 */
void World::create(const vector3du &_size) {
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

/**
 * Add a block in the map
 * @param pos
 * @param type
 * @return Success or not
 */
bool World::addBlock(const vector3du &pos, const std::string &type) {
    if (tab[pos.X][pos.Y][pos.Z])
        return false;
    tab[pos.X][pos.Y][pos.Z] = new Block(window, type, pos); // ?
    return true;
}

/**
 * Delete a block in the map
 * @param pos
 * @return Success or not
 */
bool World::removeBlock(const vector3du &pos) {
    if (!tab[pos.X][pos.Y][pos.Z])
        return false;
    delete tab[pos.X][pos.Y][pos.Z];
    tab[pos.X][pos.Y][pos.Z] = nullptr;
    return true;
}

/**
 * Check if the block can be put
 * @param randomPosX
 * @param randomPosZ
 * @return True if yes, false otherwise
 */
bool World::isValidPosition(int randomPosX, int randomPosZ) {
    /// @remark Check start coordonate in function of players numbers
    /*switch (this->nbPlayer) {
        case 1:
            return isValidOneP();
        case 2:
            return isValidOneP() && isValidTwoP();
        case 3:
            return isValidOneP() && isValidTwoP() && isValidThreeP();
        case 4:
            return isValidOneP() && isValidTwoP() && isValidThreeP() && isValidFourP();
        default:
            return true;
    }*/
    return isValidOneP(randomPosX, randomPosZ) && isValidTwoP(randomPosX, randomPosZ)
           && isValidThreeP(randomPosX, randomPosZ) && isValidFourP(randomPosX, randomPosZ);
}

bool World::isValidOneP(int posX, int posZ) {
    return !((posX == 1 && posZ == 1) || (posX == 2 && posZ == 1) || (posX == 1 && posZ == 2));
}

bool World::isValidTwoP(int posX, int posZ) {
    return !((posX == size.X - 2 && posZ == size.Z - 2) || (posX == size.X - 2 && posZ == size.Z - 3)
             || (posX == size.X - 3 && posZ == size.Z - 2));
}

bool World::isValidThreeP(int posX, int posZ) {
    return !((posX == 1 && posZ == size.Z - 2) || (posX == 1 && posZ == size.Z - 3)
             || (posX == 2 && posZ == size.Z - 2));
}

bool World::isValidFourP(int posX, int posZ) {
    return !((posX == size.X - 2 && posZ == 1) || (posX == size.X - 3 && posZ == 1)
             || (posX == size.X - 2 && posZ == 2));
}
