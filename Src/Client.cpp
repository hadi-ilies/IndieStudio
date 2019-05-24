/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Client.cpp
*/

#include <iostream> // ?
#include <thread>
#include <vector>
#include "Window.hpp"
#include "Error.hpp"
#include "World.hpp"
#include "Entity/Player.hpp"
#include "FormattedSocket.hpp"

using namespace std;
using namespace irr;
using namespace sf;

bool startTurn = false; // tmp

void serverLoop(FormattedSocket *client)
{
    while (client->receive()) {
        if (client->type != StartTurn)
            throw Error("Thread failed 1");
        startTurn = true;
        while (startTurn && client->isConnected());
    }
    if (client->isConnected())
        throw Error("Thread failed");
}

static void game(Window &window, FormattedSocket &client, World &world, vector<unique_ptr<Player>> &playerList)
{
    //World world(window, worldFileName); // TODO create with socket
    //Window window("Bomberman", dimension2d<u32>(1920, 1080), true);
    //World world(window, "TODO");
    //Player player(window, "Resources/Entity/Bomberman", "Bob", world, vector3du(1, 1, 1));
    thread loop(serverLoop, &client);

    while (window.isOpen() && client.isConnected()) {
        if (window.isKeyPressed(KEY_ESCAPE))
            window.close();
        if (startTurn) {
            if (window.isKeyPressed(KEY_KEY_Q) || window.isKeyPressed(KEY_KEY_A)) {
                if (!client.sendPlayerMove(vector2di(-1, 0)))
                    throw Error("Error SendPlayer(-1, 0)");
            }
            else if (window.isKeyPressed(KEY_KEY_D)) {
                if (!client.sendPlayerMove(vector2di(1, 0)))
                    throw Error("Error SendPlayer(1, 0)");
            }
            else if (window.isKeyPressed(KEY_KEY_Z) || window.isKeyPressed(KEY_KEY_W)) {
                if (!client.sendPlayerMove(vector2di(0, 1)))
                    throw Error("Error SendPlayer(0, 1)");
            }
            else if (window.isKeyPressed(KEY_KEY_S)) {
                if (!client.sendPlayerMove(vector2di(0, -1)))
                    throw Error("Error SendPlayer(0, -1)");
            }
            else if (window.isKeyPressed(KEY_SPACE)) {
                if (!client.sendPlayerPutBomb())
                    throw Error("Error SendPlayerBomb");
            }
            else if (!client.sendPlayerMove(vector2di(0, 0)))
                throw Error("Error sendPlayerMove(0, 0)");
            for (unique_ptr<Player> &player: playerList) {
                if (!client.receive()) {
                    cerr << "LOL I am failing " << endl;
                    //throw Error("Error client Receiver");
                }
                cerr << "YO1" << endl;
                if (client.type == PlayerMove)
                    player->move(client.dir);
                else if (client.type == PlayerPutBomb)
                    player->putBomb();
                cerr << "YO2" << endl;
                player->update();
            }
            world.update();
            startTurn = false;
        }
        bool lol = true;
        for (unique_ptr<Player> &player: playerList)
            if (!player->animHasFinished())
                lol = false;
        if (lol)
            client.sendEndTurn();
        window.display(video::SColor(255, 113, 113, 233));
    }
    client.disconnect();
    startTurn = true;
    //windowIsOpen = false;
    loop.join();
}

void client(const IpAddress &ip, const ushort &port)
{
    FormattedSocket client;
    if (!client.connect(ip, port))
        throw Error("an Error has been detected in Connect function");
    Window window("Bomberman", dimension2d<u32>(1920 / 2, 1080 / 2), false);
    size_t nbPlayers = 1;

    if (!client.receive())
        throw Error("TODO");
    if (client.type != Message)
        throw Error("TODO");
    cout << client.message << endl;
    World world(window, client.message);
    if (!client.receive())
        throw Error("TODO");
    if (client.type != DataType::Uint32)
        throw Error("TODO");
    nbPlayers = client.num;
    vector <unique_ptr<Player>> playerList;
    for (size_t i = 0; i < nbPlayers; i++)
        playerList.push_back(unique_ptr<Player>(new Player(window, "Resources/Entity/Bomberman", "Bob", world, vector3du(1, 1, 1))));
    game(window, client, world, playerList);
    //structure enum type data
    // union
}
