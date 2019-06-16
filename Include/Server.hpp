/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Server.hpp
*/

#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector> // ?
#include "World.hpp"
#include "Entity/Player.hpp"
#include "Entity/PowerUp.hpp" // ?
#include "FormattedSocket.hpp"

using namespace std;
using namespace irr;

class Server
{
public:
    Server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer);
    ~Server();

private:
    void init(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer);
    void loop();
    void addClient();
    bool clientIsConnected();

private:
    World world;
    std::vector<unique_ptr<FormattedSocket>> socketList;
    std::vector<unique_ptr<Player>> playerList;
    std::vector<unique_ptr<PowerUp>> powerUpList;
    static sf::TcpListener listener;
};

void server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer);

#endif /* !SERVER_HPP */
