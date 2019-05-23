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
    Uint32 tmp;

    if (socket.receive(packet) != Socket::Done)
        return false;
    packet >> tmp;
    type = (DataType)tmp;
    // TODO
    return true;
}

Packet &operator>>(Packet &packet, DataType &dataType)
{
    Uint32 tmp; // ??

    packet >> tmp;
    dataType = (DataType)tmp;
    return packet;
}
