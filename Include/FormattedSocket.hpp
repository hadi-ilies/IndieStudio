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

enum DataType
{
    StartTurn,
    EndTurn,
    Message,
    Number,
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
    sf::IpAddress getRemoteAddress() const;
    ushort getRemotePort() const;
    bool connect(const sf::IpAddress &remoteAddress, const ushort &remotePort, const sf::Time &timeout = sf::Time::Zero);
    bool accept(sf::TcpListener &listener); // connect for server
    void disconnect();
    bool isConnected() const;
    bool sendStartTurn();
    bool sendEndTurn();
    bool sendMessage(const std::string &msg);
    bool sendNumber(const sf::Uint32 &num);
    bool sendPosition(const vector3du &pos);
    bool sendPlayerMove(const vector2di &dir);
    bool sendPlayerPutBomb();
    //bool sendWorld(const World &world);
    //bool sendPlayer(const Player &player);
    bool receive();

private:
    bool sendPacket(sf::Packet &packet);
    bool receivePacket(sf::Packet &packet);

public:
    DataType type;
    // union // ???
    std::string message;
    sf::Uint32 number;
    vector3du position;
    vector2di direction; // TODO supr and send pos player

private:
    bool connected; // TODO set to false if Status == Socket::Disconnected or Socket::Error
    sf::TcpSocket socket;
};

sf::Packet &operator>>(sf::Packet &packet, DataType &dataType);

#endif
