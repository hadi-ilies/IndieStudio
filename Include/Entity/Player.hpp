/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>
#include <memory>

#include "Entity/Character.hpp"
#include "Entity/Bomb.hpp"
#include "Entity/PowerUp.hpp"

class Player : public Character
{
public:
    Player(Window *window, const std::string &fileName, const std::string &name, World *world, const vector3du &pos);
    ~Player();

    const uint &getBombPower() const;
    const uint &getNbBomb() const;
    const std::list<Bomb*> &getBombList() const;

public:
    bool putBomb();
    bool takePowerUp(const PowerUp &powerUp);
    void update() override;

private:
    std::string bombType;
    uint bombPower;
    uint nbBomb;
    std::list<Bomb*> bombList;
};

#endif /* !PLAYER_HPP */
