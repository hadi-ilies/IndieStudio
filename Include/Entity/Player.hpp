/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>
#include "Entity/Character.hpp"
#include "Entity/Bomb.hpp"
#include "Entity/PowerUp.hpp"

class Player : public Character
{
public:
    Player(Window *window, const std::string &fileName, const std::string &_name, World *world, const vector3du &pos);
    ~Player();
    const std::string &getName() const;
    const uint &getHp() const;
    bool putBomb();
    bool takePowerUp(const PowerUp &powerUp);
    void takeDamage();
    void update();

private:
    std::string name; // ?
    uint hp;
    std::string bombType;
    uint bombPower;
    uint nbBomb;
    std::list<unique_ptr<Bomb>> bombList;
};

#endif
