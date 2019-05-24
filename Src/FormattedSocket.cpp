/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** FormattedSocket.cpp
*/

#include "FormattedSocket.hpp"

FormattedSocket::FormattedSocket()
    : connected(false)
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
    connected = socket.connect(remoteAddress, remotePort, timeout) == Socket::Done;
    return connected;
}

bool FormattedSocket::accept(TcpListener &listener)
{
    connected = listener.accept(socket) == Socket::Done;
    return connected;
}

void FormattedSocket::disconnect()
{
    socket.disconnect();
    connected = false;
}

bool FormattedSocket::isConnected() const
{
    return connected;
}

bool FormattedSocket::sendStartTurn()
{
    Packet packet;

    packet << StartTurn;
    return sendPacket(packet);
}

bool FormattedSocket::sendMessage(const std::string &message)
{
    Packet packet;

    packet << Message;
    packet << message;
    return sendPacket(packet);
}

bool FormattedSocket::sendPlayerMove(const vector2di &dir)
{
    Packet packet;

    packet << PlayerMove;
    packet << dir.X;
    packet << dir.Y;
    return sendPacket(packet);
}

bool FormattedSocket::sendPlayerPutBomb()
{
    Packet packet;

    packet << PlayerPutBomb;
    return sendPacket(packet);
}

bool FormattedSocket::receive()
{
    Packet packet;

    if (!receivePacket(packet))
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

bool FormattedSocket::sendPacket(Packet &packet)
{
    const Socket::Status status = socket.send(packet);

    if (status == Socket::Disconnected)
        connected = false;
    return status == Socket::Done;
}

bool FormattedSocket::receivePacket(Packet &packet)
{
    const Socket::Status status = socket.receive(packet);

    if (status == Socket::Disconnected)
        connected = false;
    return status == Socket::Done;
}

Packet &operator>>(Packet &packet, DataType &dataType)
{
    Uint32 tmp;

    packet >> tmp;
    dataType = (DataType)tmp;
    return packet;
}
