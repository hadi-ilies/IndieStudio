/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Block.cpp
*/

#include "Block.hpp"
#include "Error.hpp"

/*
 * Constructors // Destructors
 */
/**
 * Create a block
 * @param window
 * @param _type
 * @param position
 */
Block::Block(Window *window, const std::string &_type, const vector3du &position)
    : type(_type), opaque(true), destructible(true),
      half(false), lifeTime(-1),
      cube(window ? window->addCube("Resources/Block/" + _type + "/Texture.png") : nullptr)
{
    const vector3df floatPos(position.X, position.Y, position.Z);

    getProperty("Resources/Block/" + _type + "/Property");
    if (window) {
        if (!cube)
            throw ERROR("Cube can't be created");
        cube->setPosition(floatPos);
    }
}

Block::~Block() {
    if (cube)
        cube->remove();
}

/*
 * Getters // Setters
 */
const std::string &Block::getType() const {
    return type;
}

const bool &Block::getOpaque() const {
    return opaque;
}

const bool &Block::getDestructible() const {
    return destructible;
}

const bool &Block::gethalf() const {
    return half;
}

const uint &Block::getLifeTime() const {
    return lifeTime;
}

/*
 * Methods
 */
void Block::update() {
    if (lifeTime && lifeTime != -1)
        lifeTime--;
}

/**
 * Create a block with property stored in a file
 * @param fileName (File Path)
 */
void Block::getProperty(const std::string &fileName) {
    std::ifstream file(fileName);
    std::string line;
    smatch match;

    if (!file)
        throw ERROR("\"" + fileName + "\" cant be opened");
    while (getline(file, line)) {
        if (regex_search(line, match, regex(R"(^opaque *: *(false|true)$)")))
            opaque = match[1] == "true";
        else if (regex_search(line, match, regex(R"(^destructible *: *(false|true)$)")))
            destructible = match[1] == "true";
        else if (regex_search(line, match, regex(R"(^half *: *(\d+)$)")))
            lifeTime = stoi(match[1]);
        else if (regex_search(line, match, regex(R"(^lifeTime *: *(\d+)$)")))
            lifeTime = stoi(match[1]);
        else
           cerr << "In file " << fileName << " unused line : {" << line << "}" << endl;
    }
}
