/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, Zappy group
 * @file Client
 */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector>
#include <thread>

#include "Window.hpp"
#include "World.hpp"
#include "Entity/Player.hpp"
#include "Entity/PowerUp.hpp"
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
