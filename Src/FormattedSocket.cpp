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

bool FormattedSocket::connect(const IpAddress &remoteAddress, const ushort &remotePort, const Time &timeout)
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

bool FormattedSocket::sendEndTurn()
{
    Packet packet;

    packet << EndTurn;
    return sendPacket(packet);
}

bool FormattedSocket::sendMessage(const std::string &msg)
{
    Packet packet;

    packet << Message;
    packet << msg;
    return sendPacket(packet);
}

bool FormattedSocket::sendNumber(const Uint32 &num)
{
    Packet packet;

    packet << Number;
    packet << num;
    return sendPacket(packet);
}

bool FormattedSocket::sendPosition(const vector3du &pos)
{
    Packet packet;

    packet << Position;
    packet << pos.X;
    packet << pos.Y;
    packet << pos.Z;
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
    else if (type == Number) {
        if (!(packet >> number))
            return false;
    }
    else if (type == Position) {
        uint x;
        uint y;
        uint z;

        if (!(packet >> x >> y >> z))
            return false;
        position.X = x;
        position.Y = y;
        position.Z = z;
    }
    else if (type == PlayerMove) {
        int x;
        int y;

        if (!(packet >> x >> y))
            return false;
        direction.X = x;
        direction.Y = y;
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
