/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Player.cpp
*/

#include "Entity/Player.hpp"

/*
 * Constructors // Desctructors
 */
Player::Player(const std::string &fileName, std::string _name, World *world, const vector3du &position) : Character(
        fileName, world, position), name(std::move(_name)), hp(1), bombType("Timer"), bombPower(2), nbBomb(1) {
}

Player::~Player() = default;

/*
 * Getters // Setters
 */
const std::string &Player::getName() const {
    return name;
}

const uint &Player::getHp() const {
    return hp;
}

/*
 * Methods
 */
bool Player::putBomb() {
    const vector3df floatPosition(position.X, position.Y, position.Z);

    if (bombList.size() >= nbBomb)
        return false;
    if (!animHasFinished())
        return false;
    changeModel("Put");
    if ((anim = Window::getInstance().createTranslation(floatPosition, floatPosition, TIMESTAMP)))
        mesh->addAnimator(anim);
    bombList.push_back(unique_ptr<Bomb>(new Bomb(bombType, bombPower, world, position)));
    return true;
}

bool Player::takePowerUp(const PowerUp &powerUp) {
    if (powerUp.getType() == "FireUp")
        bombPower++;
    else if (powerUp.getType() == "BombUp")
        nbBomb++;
    else
        return false;
    return true;
}

void Player::takeDamage() {
    if (hp) {
        hp--;
        if (!hp)
            //mesh->setVisible(false); // ??
            mesh->setRotation(vector3df(0, 0, 90));
    }
}

void Player::update() {
    Entity::update();
    for (unique_ptr<Bomb> &bomb : bombList) // TODO fusion of two for
        bomb->update();
    for (auto it = bombList.begin() ; it != bombList.end() ;)
        if (!(*it)->getPower())
            it = bombList.erase(it);
        else
            it++;
}
