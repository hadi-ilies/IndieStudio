/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector> // ?
#include <thread>
#include "Window.hpp"
#include "World.hpp"
#include "Entity/Player.hpp"
#include "Entity/PowerUp.hpp" // ?
#include "FormattedSocket.hpp"

using namespace std;

/**
 * @namespace Irrlicht
 */
using namespace irr;

/**
 * Player action enum
 */
enum PlayerAction {
    None,
    Exit,
    Save, Up,
    Down,
    Left,
    Right,
    PutBomb
};

/**
 * Player type (Human or AI)
 */
enum PlayerType{
    Human,
    IACorentin
};

bool client(Window *window, Player *myPlayer, const PlayerType &playerType, const sf::IpAddress &ip, const ushort &port);

#endif /* !CLIENT_HPP */
