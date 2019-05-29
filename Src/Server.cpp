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
#include "Error.hpp"
#include "FormattedSocket.hpp"

using namespace std;
using namespace irr;
using namespace sf;

void server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer)
{
    //Window window("Bomberman", dimension2d<u32>(800, 600), false);
    World world(NULL, worldFileName);
    std::vector<unique_ptr<Player>> playerList;

    TcpListener listener;
    std::vector<unique_ptr<FormattedSocket>> socketList;

    cerr << "start server" << endl;
    if (listener.listen(port) != Socket::Done)
        throw Error("listen failed");
    while (playerList.size() < nbPlayer) {
        unique_ptr<FormattedSocket> socket = unique_ptr<FormattedSocket>(new FormattedSocket);
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
            unique_ptr<Player> player = unique_ptr<Player>(new Player(NULL, fileName, name, &world, vector3du(1, 1, 1))); // TODO change pos

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
    for (size_t id = 0; id < socketList.size(); id++) {
        socketList[id]->sendMessage(worldFileName);
        socketList[id]->sendNumber(socketList.size());
        for (unique_ptr<Player> &player : playerList) {
            socketList[id]->sendMessage(player->getFileName());
            socketList[id]->sendMessage(player->getTexture());
            socketList[id]->sendMessage(player->getName());
            if (id == 1)
                socketList[id]->sendPosition(vector3du(1, 1, world.getSize().Z - 2));
            else if (id == 2)
                socketList[id]->sendPosition(vector3du(world.getSize().X - 2, 1, 1));
            else if (id == 3)
                socketList[id]->sendPosition(vector3du(world.getSize().X - 2, 1, world.getSize().Z - 2));
            else
                socketList[id]->sendPosition(vector3du(1, 1, 1)); // tmp get dynamic pos
        }
        socketList[id]->sendNumber(id);
    }

    // loop
    while (!socketList.empty()) {
        cerr << "start turn : ";
        for (unique_ptr<FormattedSocket> &socket : socketList)
            if (!socket->sendStartTurn())
                throw Error("send failed");
        cerr << "OK" << endl;
        cerr << "receive action : ";
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
