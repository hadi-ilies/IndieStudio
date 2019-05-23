/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Sender.hpp
*/

#ifndef SENDER_HPP
#define SENDER_HPP

#include <SFML/Network.hpp>
#include "World.hpp"
#include "Entity/Player.hpp"

using namespace std;
using namespace sf;

enum dataType
{
    StartTurn,
    Message,
    // ...
};

struct Data
{
    dataType type;
    union data
    {
        std::string message;
    };
};

class Sender
{
public:
    Sender(TcpSocket &_socket);
    ~Sender();
    Socket::Status sendStartTurn();
    Socket::Status sendMessage(const std::string &message);
    //Status sendWorld(const World &world);
    //Status sendPlayer(const Player &player);

private:
    TcpSocket &socket;
};

#endif
