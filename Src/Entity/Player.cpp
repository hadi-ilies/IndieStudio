/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Player.cpp
*/

#include "Entity/Player.hpp"

Player::Player(Window *window, const std::string &fileName, const std::string &_name, World *world, const vector3du &position)
    : Character(window, fileName, world, position), name(_name), bombType("Timer"), bombPower(2), nbBomb(1)
{
}

Player::~Player()
{
}

const std::string &Player::getName() const
{
    return name;
}

#include <iostream> // tmp
bool Player::putBomb()
{
    const vector3df floatPosition(position.X, position.Y, position.Z);

    if (bombList.size() >= nbBomb)
        return false;
    if (!animHasFinished())
        return false;
    changeModel("Put");
    if (anim = window->createTranslation(floatPosition, floatPosition, TIMESTAMP))
        mesh->addAnimator(anim);
    bombList.push_back(unique_ptr<Bomb>(new Bomb(window, bombType, bombPower, world, position)));
    return true;
}

bool Player::takePowerUp(const PowerUp &powerUp)
{
    if (powerUp.getType() == "FireUp")
        bombPower++;
    else if (powerUp.getType() == "BombUp")
        nbBomb++;
    else
        return false;
    return true;
}

void Player::update()
{
    Entity::update();
    for (unique_ptr<Bomb> &bomb : bombList) // TODO fusion of two for
        bomb->update();
    for (auto it = bombList.begin(); it != bombList.end();)
        if (!(*it)->getPower())
            it = bombList.erase(it);
        else
            it++;
}
