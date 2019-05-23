/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** FormattedSocket.hpp
*/

#ifndef FORMATTEDSOCKET_HPP
#define FORMATTEDSOCKET_HPP

#include <SFML/Network.hpp>
#include "World.hpp" // ?
#include "Entity/Player.hpp" // ?

using namespace std;
using namespace sf;

enum DataType
{
    StartTurn,
    Message,
    PlayerMove,
    PlayerPutBomb,
};

class FormattedSocket
{
public:
    FormattedSocket();
    ~FormattedSocket();
    ushort getLocalPort() const;
    IpAddress getRemoteAddress() const;
    ushort getRemotePort() const;
    bool connect(const IpAddress &remoteAddress, ushort remotePort, Time timeout=Time::Zero);
    void disconnect();
    bool isConnected() const;
    bool sendStartTurn();
    bool sendMessage(const std::string &message);
    bool sendPlayerMove(const vector2di &dir);
    bool sendPlayerPutBomb();
    //bool sendWorld(const World &world);
    //bool sendPlayer(const Player &player);
    bool receive();

public:
    DataType type;
    // union // ???
    std::string message;
    vector2di dir;

//private: // tmp
    bool connected; // TODO set to false if Status == Socket::Disconnected or Socket::Error
    TcpSocket socket;
};

Packet &operator>>(Packet &packet, DataType &dataType);

#endif
