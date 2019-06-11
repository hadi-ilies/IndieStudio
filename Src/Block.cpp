/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Block.cpp
*/

#include "Block.hpp"
#include "Error.hpp"

/*
 * Constructors // Destructors
 */
Block::Block(const std::string &_type, const vector3du &position) : type(_type), lifeTime(-1), cube(Window::getInstance().addCube(
        "Resources/Block/" + _type + "/Texture.png")) {
    getProperty("Resources/Block/" + _type + "/Property");
    const vector3df floatPos(position.X, position.Y, position.Z);
    if (!cube)
        throw Error("Cube can't be created", __FILE__, __FUNCTION__, __LINE__);
    cube->setPosition(floatPos);
}

Block::~Block() {
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

void Block::getProperty(const std::string &fileName) {
    std::ifstream file(fileName);
    std::string line;
    smatch match;

    if (!file)
        throw Error("\"" + fileName + "\" cant be opened", __FILE__, __FUNCTION__, __LINE__);
    while (getline(file, line)) {
        if (regex_search(line, match, regex(R"(^opaque *: *(false|true)$)")))
            opaque = match[1] == "true";
        else if (regex_search(line, match, regex(R"(^destructible *: *(false|true)$)")))
            destructible = match[1] == "true";
        else if (regex_search(line, match, regex(R"(^lifeTime *: *(\d+)$)")))
            lifeTime = stoi(match[1]);
    }
}
