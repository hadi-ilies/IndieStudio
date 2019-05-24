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
bool endTurn = false;
enum Command {UP, DOWN, LEFT, RIGHT, DROPBOMB};

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

static bool turnhasfinished(vector<unique_ptr<Player>> &playerList)
{
    bool check = true;

    for (unique_ptr<Player> &player: playerList)
        if (!player->animHasFinished())
            check = false;
    return check;
}

static Command getKey(Window &window)
{
    Command key;
    if (window.isKeyPressed(KEY_SPACE))
        key = DROPBOMB;
    else if (window.isKeyPressed(KEY_KEY_Q) || window.isKeyPressed(KEY_KEY_A))
        key = LEFT;
    else if (window.isKeyPressed(KEY_KEY_D))
        key = RIGHT;
    else if (window.isKeyPressed(KEY_KEY_Z) || window.isKeyPressed(KEY_KEY_W))
        key = UP;
    else if (window.isKeyPressed(KEY_KEY_S))
        key = DOWN;
    return key;
}

static void Commands(Command &key, FormattedSocket &client, World &world, vector<unique_ptr<Player>> &playerList)
{
    if (key == DROPBOMB) {
        if (!client.sendPlayerPutBomb())
            throw Error("Error SendPlayerBomb");
        }
        else if (key == LEFT) {
            if (!client.sendPlayerMove(vector2di(-1, 0)))
                throw Error("Error SendPlayer(-1, 0)");
        }
        else if (key == RIGHT) {
            if (!client.sendPlayerMove(vector2di(1, 0)))
                throw Error("Error SendPlayer(1, 0)");
        }
        else if (key == UP) {
            if (!client.sendPlayerMove(vector2di(0, 1)))
                throw Error("Error SendPlayer(0, 1)");
        }
        else if (key == DOWN) {
            if (!client.sendPlayerMove(vector2di(0, -1)))
                throw Error("Error SendPlayer(0, -1)");
        }
        else if (!client.sendPlayerMove(vector2di(0, 0)))
            throw Error("Error sendPlayerMove(0, 0)");
        for (unique_ptr<Player> &player: playerList) {
            if (!client.receive())
                throw Error("Error client Receiver");
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
        endTurn = true;
}

static void game(Window &window, FormattedSocket &client, World &world, vector<unique_ptr<Player>> &playerList)
{
    thread loop(serverLoop, &client);
    Command key;

    while (window.isOpen() && client.isConnected()) {
        if (window.isKeyPressed(KEY_ESCAPE))
            window.close();
        key = getKey(window);
        if (startTurn)
            Commands(key, client, world, playerList);
        if (endTurn) {
            if (turnhasfinished(playerList)) {
                client.sendEndTurn();
                endTurn = false;
            }
        }
        window.display(video::SColor(255, 113, 113, 233));
    }
    client.disconnect();
    startTurn = true;
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
        throw Error("receive error 1");
    if (client.type != Message)
        throw Error("message error");
    cout << client.message << endl;
    World world(window, client.message);
    if (!client.receive())
        throw Error("receive error 2");
    if (client.type != DataType::Uint32)
        throw Error("uint 32 error");
    nbPlayers = client.num;
    vector <unique_ptr<Player>> playerList;
    for (size_t i = 0; i < nbPlayers; i++)
        playerList.push_back(unique_ptr<Player>(new Player(window, "Resources/Entity/Bomberman", "Bob", world, vector3du(1, 1, 1))));
    //playerList.front()->changeTexture("Dark"); // tmp in menu
    game(window, client, world, playerList);
    //structure enum type data
    // union
}
