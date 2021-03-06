/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player.cpp
*/

#include "Entity/Player.hpp"

/*
 * Constructors // Destructors
 */
Player::Player(Window *window, const std::string &fileName, const std::string &name, World *world,
               const vector3du &position) : Character(window, fileName, world, name, position),
                                            bombType("Timer"), bombPower(2), nbBomb(1) {
    if (window) {
        JukeBox::getInstance().addSound("PutBomb", "Resources/Sound/PutBomb.ogg");
        JukeBox::getInstance().addSound("TakePowerUp", "Resources/Sound/TakePowerUp.ogg");
    }
}

Player::~Player() {
    for (Bomb *bomb : bombList)
        delete bomb;
}

/*
 * Getters // Setters
 */
const uint &Player::getBombPower() const {
    return bombPower;
}

const uint &Player::getNbBomb() const {
    return nbBomb;
}

const std::list<Bomb *> &Player::getBombList() const {
    return bombList;
}

/*
 * Methods
 */
/**
 * Put the bomb at the position
 * @return True if possible to put the bomb, false otherwise
 */
bool Player::putBomb() {
    const vector3df floatPosition(position.X, position.Y, position.Z);

    if (bombList.size() >= nbBomb)
        return false;
    if (!animHasFinished())
        return false;
    if (window) {
        JukeBox::getInstance().playSound("PutBomb");
        changeModel("Put");
        if ((anim = window->createTranslation(floatPosition, floatPosition, TIMESTAMP)))
            mesh->addAnimator(anim);
    }
    bombList.push_back(new Bomb(window, bombType, bombPower, world, position));
    return true;
}

/**
 * Take the power up
 * @param powerUp
 * @return True if success, false otherwise
 */
bool Player::takePowerUp(const PowerUp &powerUp) {
    if (window)
        JukeBox::getInstance().playSound("TakePowerUp");
    if (powerUp.getType() == "FireUp")
        bombPower++;
    else if (powerUp.getType() == "BombUp")
        nbBomb++;
    else
        return false;
    return true;
}

/**
 * Update the player's bomb list
 */
void Player::update() {
    Entity::update();
    for (auto it = bombList.begin() ; it != bombList.end() ;) {
        (*it)->update();
        if (!(*it)->getPower()) {
            delete *it;
            it = bombList.erase(it);
        } else
            it++;
    }
}
