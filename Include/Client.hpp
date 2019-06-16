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
using namespace irr;

#define LOCAL_ADDRESS sf::IpAddress::getLocalAddress().toString()

enum PlayerAction {None, Exit, Save, Up, Down, Left, Right, PutBomb};
enum PlayerType {Human, IACorentin};

/*class Client
{
public:
    Client(Window *window, Player *myPlayer, const PlayerType &playerType, const sf::IpAddress &ip, const ushort &port);
    bool run();

private:
    void init();
    void game();

private:
    // var
};*/

bool client(Window *window, Player *myPlayer, const PlayerType &playerType, const sf::IpAddress &ip, const ushort &port);

#endif /* !CLIENT_HPP */
