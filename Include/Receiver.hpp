/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Receiver.hpp
*/

#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include <SFML/Network.hpp>
#include "DataType.hpp"
#include "World.hpp" // ?
#include "Entity/Player.hpp" // ?

using namespace std;
using namespace sf;

class Receiver
{
public:
    Receiver(TcpSocket &_socket);
    ~Receiver();
    bool receive();

public:
    DataType type;
    union
    {
        std::string message;
    };

private:
    TcpSocket &socket;
};

Packet &operator>>(Packet &packet, DataType &dataType);

#endif
