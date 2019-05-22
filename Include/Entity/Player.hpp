/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>
#include <SFML/Network.hpp>
#include "Entity/Character.hpp"
#include "Entity/Bomb.hpp"

using namespace sf;

class Player : public Character
{
public:
    Player(Window &window, const std::string &fileName, const std::string &_name, World &world, const vector3du &pos);
    ~Player();
    bool putBomb();
    void update();
    void aff();

private:
    TcpSocket socket;
    std::string name; // ?
    std::string bombType;
    uint bombPower;
    uint nbBomb;
    std::list<unique_ptr<Bomb>> bombList;
};

#endif
