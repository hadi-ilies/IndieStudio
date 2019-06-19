/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, Zappy group
 * @file Server
 */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>

#include "World.hpp"
#include "Entity/Player.hpp"
#include "Entity/PowerUp.hpp"
#include "FormattedSocket.hpp"

using namespace std;

/**
 * @namespace Irrlicht
 */
using namespace irr;

class Server {
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
