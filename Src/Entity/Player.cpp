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
Player::Player(Window *window, const std::string &fileName, std::string _name, World *world, const vector3du &position)
    : Character(window, fileName, world, std::move(_name), position), bombType("Timer"),
      bombPower(2), nbBomb(1)
{
    if (window) {
        JukeBox::getInstance().addSound("Damage", "Resources/Sound/Damage.ogg");
        JukeBox::getInstance().addSound("PutBomb", "Resources/Sound/PutBomb.ogg");
        JukeBox::getInstance().addSound("TakePowerUp", "Resources/Sound/TakePowerUp.ogg");
    }
}

Player::~Player()
{
    for (Bomb *bomb : bombList)
        delete bomb;
}

/*
 * Getters // Setters
 */
const uint &Player::getBombPower() const
{
    return bombPower;
}

const uint &Player::getNbBomb() const
{
    return nbBomb;
}

const std::list<Bomb *> &Player::getBombList() const
{
    return bombList;
}

/*
 * Methods
 */
bool Player::putBomb()
{
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

bool Player::takePowerUp(const PowerUp &powerUp)
{
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

bool Player::takeDamage()
{
    if (hp) {
        hp--;
        if (window)
            JukeBox::getInstance().playSound("Damage");
        if (!hp)
            if (mesh)
                //mesh->setVisible(false); // ??
                mesh->setRotation(vector3df(0, 0, 90));
    }
    return !hp;
}

void Player::update()
{
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
