/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Receiver.cpp
*/

#include "Receiver.hpp"

Receiver::Receiver(TcpSocket &_socket)
    : socket(_socket)
{
}

Receiver::~Receiver()
{
}

bool Receiver::receive()
{
    Packet packet;

    if (socket.receive(packet) != Socket::Done)
        return false;
    if (!(packet >> type))
        return false;
    if (type == Message) {
        if (!(packet >> message))
            return false;
    }
    else if (type == PlayerMove) {
        int x;
        int y;

        if (!(packet >> x >> y))
            return false;
        dir.X = x;
        dir.Y = y;
    }
    //else if (type == ...) // TODO
    return true;
}

Packet &operator>>(Packet &packet, DataType &dataType)
{
    Uint32 tmp;

    packet >> tmp;
    dataType = (DataType)tmp;
    return packet;
}
