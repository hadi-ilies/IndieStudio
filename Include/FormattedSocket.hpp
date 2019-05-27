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
    EndTurn,
    Message,
    Uint32,
    Position,
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
    bool accept(TcpListener &listener); // connect for server
    void disconnect();
    bool isConnected() const;
    bool sendStartTurn();
    bool sendEndTurn();
    bool sendMessage(const std::string &message);
    bool sendUint32(const sf::Uint32 &nb);
    bool sendPosition(const vector3du &pos);
    bool sendPlayerMove(const vector2di &dir);
    bool sendPlayerPutBomb();
    //bool sendWorld(const World &world);
    //bool sendPlayer(const Player &player);
    bool receive();

private:
    bool sendPacket(Packet &packet);
    bool receivePacket(Packet &packet);

public:
    DataType type;
    // union // ???
    std::string message;
    sf::Uint32 num;
    vector3du pos;
    vector2di dir;

private:
    bool connected; // TODO set to false if Status == Socket::Disconnected or Socket::Error
    TcpSocket socket;
};

Packet &operator>>(Packet &packet, DataType &dataType);

#endif
