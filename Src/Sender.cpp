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

Socket::Status Sender::sendStartTurn()
{
    Packet packet;

    packet << StartTurn;
    return socket.send(packet);
}

Socket::Status Sender::sendMessage(const std::string &message)
{
    Packet packet;

    packet << Message;
    packet << message;
    return socket.send(packet);
}
