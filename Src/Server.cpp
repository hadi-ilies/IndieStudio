#include <memory>

/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Server.cpp
*/

#include <iostream> // ?
#include <vector> // ?
#include "Window.hpp"
#include "World.hpp"
#include "Entity/Player.hpp"
#include "Entity/PowerUp.hpp" // ?
#include "Error.hpp"
#include "FormattedSocket.hpp"

using namespace std;
using namespace irr;

void server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer)
{
    World world("Resources/Map/" + worldFileName);
    std::vector<unique_ptr<Player>> playerList;
    std::vector<unique_ptr<PowerUp>> powerUpList;

    for (uint i = 0; i < world.getSize().X; i++)
        for (uint j = 0; j < world.getSize().Y; j++)
            for (uint k = 0; k < world.getSize().Z; k++)
                if (world.getBlock(vector3du(i, j, k)) && world.getBlock(vector3du(i, j, k))->getDestructible() && rand() % 2)
                    powerUpList.push_back(std::make_unique<PowerUp>(rand() %  2 ? "FireUp" : "BombUp", &world, vector3du(i, j, k))); // tmp type
    sf::TcpListener listener;
    std::vector<unique_ptr<FormattedSocket>> socketList;

    cerr << "start server" << endl;
    if (listener.listen(port) != sf::Socket::Done)
        throw Error("listen failed");
    while (playerList.size() < nbPlayer) {
        unique_ptr<FormattedSocket> socket = std::make_unique<FormattedSocket>();
        std::string fileName;
        std::string texture;
        std::string name;

        if (!socket->accept(listener))
            throw Error("accept failed");
        cerr << "new client" << endl;
        if (!socket->receive())
            throw Error("receive failed");
        if (socket->type != Message)
            throw Error("bad type");
        fileName = socket->message;
        if (!socket->receive())
            throw Error("receive failed");
        if (socket->type != Message)
            throw Error("bad type");
        texture = socket->message;
        if (!socket->receive())
            throw Error("receive failed");
        if (socket->type != Message)
            throw Error("bad type");
        name = socket->message;
        try {
            vector3du position = vector3du(1, 1, 1); // TODO change pos

            if (playerList.size() == 1)
                position = vector3du(1, 1, world.getSize().Z - 2);
            else if (playerList.size() == 2)
                position = vector3du(world.getSize().X - 2, 1, 1);
            else if (playerList.size() == 3)
                position = vector3du(world.getSize().X - 2, 1, world.getSize().Z - 2);
            unique_ptr<Player> player = unique_ptr<Player>(new Player(fileName, name, &world, position));

            player->changeTexture(texture);
            //throw Error("texture doesn't exist");
            playerList.push_back(move(player));
            socketList.push_back(move(socket));
            cerr << "client validate" << endl;
        }
        catch (const exception &e) {
            cerr << "ERROR : " << e.what() << endl;
            cerr << "client reject" << endl;
        }
    }
    listener.close();
    cerr << "clients connected" << endl;

    // init
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

    // loop
    while (!socketList.empty()) {
        cerr << "start turn : ";
        for (unique_ptr<FormattedSocket> &socket : socketList)
            if (!socket->sendStartTurn())
                throw Error("send failed");
        cerr << "OK" << endl;
        cerr << "receive action : ";
        /*
          for (size_t i = 0; i < socketList.size(); i++) {
          if (!socketList[i]->receive())
          throw Error("receiver failed");
          if (socketList[i]->type == PlayerMove)
          playerList[i]->move(socketList[i]->direction);
          else if (socketList[i]->type == PlayerPutBomb)
          playerList[i]->putBomb();
          else
          throw Error("bad type");
          }
         */
        for (unique_ptr<FormattedSocket> &socket : socketList)
            if (!socket->receive())
                throw Error("receiver failed");
        cerr << "OK" << endl;
        cerr << "transmit action : ";
        for (unique_ptr<FormattedSocket> &socket : socketList)
            for (unique_ptr<FormattedSocket> &socket2 : socketList)
                if (socket2->type == PlayerMove) {
                    if (!socket->sendPlayerMove(socket2->direction)) // tmp
                        throw Error("send failed");
                }
                else if (socket2->type == PlayerPutBomb) {
                    if (!socket->sendPlayerPutBomb()) // tmp
                        throw Error("send failed");
                }
                else
                    throw Error("bad type");
        cerr << "OK" << endl;
        cerr << "end turn : ";
        for (unique_ptr<FormattedSocket> &socket : socketList) {
            if (!socket->receive())
                throw Error("receiver failed");
            if (socket->type != EndTurn)
                throw Error("bad type");
        }
        cerr << "OK" << endl;
    }
    cerr << "stop server" << endl;
}
