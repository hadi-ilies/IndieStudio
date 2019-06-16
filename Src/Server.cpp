/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Server.cpp
*/

#include <iostream> // ?
#include "Server.hpp"
#include "Error.hpp"

sf::TcpListener Server::listener;

Server::Server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer)
    : world(nullptr, "Resources/Map/Game/" + worldFileName)
{
    for (uint i = 0; i < world.getSize().X; i++)
        for (uint j = 0; j < world.getSize().Y; j++)
            for (uint k = 0; k < world.getSize().Z; k++)
                if (world.getBlock(vector3du(i, j, k)) && world.getBlock(vector3du(i, j, k))->getDestructible() && rand() % 4 == 0)
                    powerUpList.push_back(make_unique<PowerUp>(nullptr, rand() %  2 ? "FireUp" : "BombUp", &world, vector3du(i, j, k))); // tmp type
    init(port, worldFileName, nbPlayer);
    loop();
}

Server::~Server()
{
    for (unique_ptr<FormattedSocket> &socket : socketList) // remove disconnect all player
        if (socket->isConnected())
            socket->disconnect();
}

void Server::init(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer)
{

    if (listener.getLocalPort() == 0)
        if (listener.listen(port) != sf::Socket::Done)
            throw ERROR("Listen failed");
    while (playerList.size() < nbPlayer)
        addClient();
    //listener.close();
    cerr << "clients connected" << endl;

    for (size_t i = 0; i < socketList.size(); i++) {
        socketList[i]->sendMessage(worldFileName);
        socketList[i]->sendNumber(powerUpList.size());
        for (unique_ptr<PowerUp> &powerUp : powerUpList) {
            socketList[i]->sendMessage(powerUp->getType());
            socketList[i]->sendPosition(powerUp->getPosition());
        }
        socketList[i]->sendNumber(socketList.size());
        for (unique_ptr<Player> &player : playerList) {
            socketList[i]->sendMessage(player->getFileName());
            socketList[i]->sendMessage(player->getTexture());
            socketList[i]->sendMessage(player->getName());
            socketList[i]->sendPosition(player->getPosition());
        }
        socketList[i]->sendNumber(i);
    }
}

void Server::loop()
{
    while (!socketList.empty() && clientIsConnected()) {
        for (unique_ptr<FormattedSocket> &socket : socketList) // start turn
            if (socket->isConnected())
                if (!socket->sendStartTurn())
                    throw ERROR("Send failed");
        for (unique_ptr<FormattedSocket> &socket : socketList) // wait player
            if (socket->isConnected())
                if (!socket->receive())
                    throw ERROR("Receiver failed");
        for (unique_ptr<FormattedSocket> &socket : socketList) // send info
            if (socket->isConnected())
                for (unique_ptr<FormattedSocket> &socket2 : socketList)
                    if (!socket2->isConnected()) {
                        if (!socket->sendPlayerMove(vector2di(0, 0)))
                            throw ERROR("Send failed");
                    }
                    else {
                        if (socket2->type == PlayerMove) {
                            if (!socket->sendPlayerMove(socket2->direction))
                                throw ERROR("Send failed");
                        }
                        else if (socket2->type == PlayerPutBomb) {
                            if (!socket->sendPlayerPutBomb())
                                throw ERROR("Send failed");
                        }
                        else if (socket2->type == PlayerDisconnect) {
                            if (!socket->sendPlayerDisconnect())
                                throw ERROR("Send failed");
                        }
                        else
                            throw ERROR("Bad type");
                    }
        for (unique_ptr<FormattedSocket> &socket : socketList) // remove disconnect player
            if (socket->isConnected())
                if (socket->type == PlayerDisconnect) {
                    cerr << "Player Disconnect" << endl;
                    socket->disconnect();
                }
        for (unique_ptr<FormattedSocket> &socket : socketList) // end turn
            if (socket->isConnected()) {
                if (!socket->receive())
                    throw ERROR("Receiver failed");
                if (socket->type != EndTurn)
                    throw ERROR("Bad type");
            }
    }
}

void Server::addClient()
{
    unique_ptr<FormattedSocket> socket = make_unique<FormattedSocket>();
    std::string fileName;
    std::string texture;
    std::string name;

    if (!socket->accept(listener))
        throw ERROR("Accept failed");
    cerr << "new client" << endl;
    if (!socket->receive())
        throw ERROR("Listen failed");
    if (socket->type != Message)
        throw ERROR("Bad type");
    fileName = socket->message;
    if (!socket->receive())
        throw ERROR("Receive failed");
    if (socket->type != Message)
        throw ERROR("Bad type");
    texture = socket->message;
    if (!socket->receive())
        throw ERROR("Receive failed");
    if (socket->type != Message)
        throw ERROR("Bad type");
    name = socket->message;
    try {
        vector3du position = vector3du(1, 1, 1); // TODO change pos

        if (playerList.size() == 1)
            position = vector3du(1, 1, world.getSize().Z - 2);
        else if (playerList.size() == 2)
            position = vector3du(world.getSize().X - 2, 1, 1);
        else if (playerList.size() == 3)
            position = vector3du(world.getSize().X - 2, 1, world.getSize().Z - 2);
        unique_ptr<Player> player = make_unique<Player>(nullptr, fileName, name, &world, position);

        if (!player->changeTexture(texture))
            throw ERROR("texture doesn't exist");
        playerList.push_back(move(player));
        socketList.push_back(move(socket));
        cerr << "client validate" << endl;
    }
    catch (const exception &e) {
        cerr << "ERROR : " << e.what() << endl;
        cerr << "client reject" << endl;
    }
}

bool Server::clientIsConnected()
{
    for (unique_ptr<FormattedSocket> &socket : socketList)
        if (socket->isConnected())
            return true;
    return false;
}

void server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer)
{
    try {
        Server svr(port, worldFileName, nbPlayer);
    }
    catch (const Error &e) {
        std::cerr << "[" << e.where() << "]" << std::endl;
        std::cerr << "\t" << e.what() << std::endl;
    }
    catch (const exception &e) {
        std::cerr << "EXCEPTION : " << e.what() << std::endl;
    }
}
