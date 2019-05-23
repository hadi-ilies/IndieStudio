/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Sender.hpp
*/

#ifndef SENDER_HPP
#define SENDER_HPP

#include <SFML/Network.hpp>
#include "DataType.hpp"
#include "World.hpp" // ?
#include "Entity/Player.hpp" // ?

using namespace std;
using namespace sf;

class Sender
{
public:
    Sender(TcpSocket &_socket);
    ~Sender();
    bool sendStartTurn();
    bool sendMessage(const std::string &message);
    //bool sendWorld(const World &world);
    //bool sendPlayer(const Player &player);

private:
    TcpSocket &socket;
};

#endif
