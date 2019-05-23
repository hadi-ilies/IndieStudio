/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** FormattedSocket.cpp
*/

#include "FormattedSocket.hpp"

FormattedSocket::FormattedSocket()
{
}

FormattedSocket::~FormattedSocket()
{
}

ushort FormattedSocket::getLocalPort() const
{
    return socket.getLocalPort();
}

IpAddress FormattedSocket::getRemoteAddress() const
{
    return socket.getRemoteAddress();
}

ushort FormattedSocket::getRemotePort() const
{
    return socket.getRemotePort();
}

bool FormattedSocket::connect(const IpAddress &remoteAddress, ushort remotePort, Time timeout)
{
    return socket.connect(remoteAddress, remotePort, timeout) == Socket::Done;
}

void FormattedSocket::disconnect()
{
    socket.disconnect();
}


bool FormattedSocket::sendStartTurn()
{
    Packet packet;

    packet << StartTurn;
    return socket.send(packet) == Socket::Done;
}

bool FormattedSocket::sendMessage(const std::string &message)
{
    Packet packet;

    packet << Message;
    packet << message;
    return socket.send(packet) == Socket::Done;
}

bool FormattedSocket::sendPlayerMove(const vector2di &dir)
{
    Packet packet;

    packet << PlayerMove;
    packet << dir.X;
    packet << dir.Y;
    return socket.send(packet) == Socket::Done;
}

bool FormattedSocket::sendPlayerPutBomb()
{
    Packet packet;

    packet << PlayerPutBomb;
    return socket.send(packet) == Socket::Done;
}

bool FormattedSocket::receive()
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
