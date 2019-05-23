/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Sender.cpp
*/

#include "Sender.hpp"

Sender::Sender(TcpSocket &_socket)
    : socket(_socket)
{
}

Sender::~Sender()
{
}

bool Sender::sendStartTurn()
{
    Packet packet;

    packet << StartTurn;
    return socket.send(packet) == Socket::Done;
}

bool Sender::sendMessage(const std::string &message)
{
    Packet packet;

    packet << Message;
    packet << message;
    return socket.send(packet) == Socket::Done;
}

bool Sender::sendPlayerMove(const vector2di &dir)
{
    Packet packet;

    PlayerMove << PlayerMove;
    PlayerMove << dir.X;
    PlayerMove << dir.Y;
    return socket.send(packet) == Socket::Done;
}

bool Sender::sendPlayerPutBomb()
{
    Packet packet;

    packet << PlayerPutBomb;
    return socket.send(packet) == Socket::Done;
}
