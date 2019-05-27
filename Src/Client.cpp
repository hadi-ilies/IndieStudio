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

bool startTurn = false; // tmp no global
bool endTurn = false; // tmp no global

enum PlayerAction {None, Up, Down, Left, Right, PutBomb};

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

static bool turnHasFinished(vector<unique_ptr<Player>> &playerList)
{
    bool check = true;

    for (unique_ptr<Player> &player: playerList)
        if (!player->animHasFinished())
            check = false;
    return check;
}

static bool getKey(const Window &window, PlayerAction &key)
{
    if (window.isKeyPressed(KEY_SPACE))
        key = PutBomb;
    else if (window.isKeyPressed(KEY_KEY_Q) || window.isKeyPressed(KEY_KEY_A))
        key = Left;
    else if (window.isKeyPressed(KEY_KEY_D) || window.isKeyPressed(KEY_KEY_E))
        key = Right;
    else if (window.isKeyPressed(KEY_KEY_Z) || window.isKeyPressed(KEY_KEY_W))
        key = Up;
    else if (window.isKeyPressed(KEY_KEY_S))
        key = Down;
    else
        return false;
    return true;
}

static void execPlayerAction(PlayerAction &key, FormattedSocket &client, World &world, vector<unique_ptr<Player>> &playerList)
{
    if (key == PutBomb) {
        if (!client.sendPlayerPutBomb())
            throw Error("SendPlayerBomb");
    }
    else if (key == Left) {
        if (!client.sendPlayerMove(vector2di(-1, 0)))
            throw Error("SendPlayer(-1, 0)");
    }
    else if (key == Right) {
        if (!client.sendPlayerMove(vector2di(1, 0)))
            throw Error("SendPlayer(1, 0)");
    }
    else if (key == Up) {
        if (!client.sendPlayerMove(vector2di(0, 1)))
            throw Error("SendPlayer(0, 1)");
    }
    else if (key == Down) {
        if (!client.sendPlayerMove(vector2di(0, -1)))
            throw Error("SendPlayer(0, -1)");
    }
    else if (!client.sendPlayerMove(vector2di(0, 0)))
        throw Error("sendPlayerMove(0, 0)");
    for (unique_ptr<Player> &player: playerList) {
        if (!client.receive())
            throw Error("client Receiver");
        if (client.type == PlayerMove)
            player->move(client.dir);
        else if (client.type == PlayerPutBomb)
            if (!player->putBomb())
                player->move(vector2di(0, 0));
        player->update();
    }
    world.update();
    startTurn = false;
    endTurn = true;
}

static void game(Window &window, FormattedSocket &client, World &world, vector<unique_ptr<Player>> &playerList)
{
    thread loop(serverLoop, &client);
    PlayerAction key = None;

    while (window.isOpen() && client.isConnected()) {
        if (window.isKeyPressed(KEY_ESCAPE))
            window.close();
        getKey(window, key);
        if (startTurn)
            execPlayerAction(key, client, world, playerList);
        if (endTurn)
            if (turnHasFinished(playerList)) {
                if (!client.sendEndTurn())
                    throw Error("sendEndTurn failed");
                endTurn = false;
                key = None;
            }
        window.display(video::SColor(255, 113, 113, 233));
    }
    client.disconnect();
    startTurn = true; // for exit thread
    loop.join();
}

void client(const IpAddress &ip, const ushort &port) //put player in param
{
    FormattedSocket client;
    Window window("Bomberman", dimension2d<u32>(1920 / 2, 1080 / 2), false);
    World myWorld(window, "TODO"); // Todo put pointer on world constructor. this we allow us to put NULL in constructor
    Player myPlayer(window, "Bomberman", "Bob", myWorld, vector3du(1, 1 ,1));
    myPlayer.changeTexture("Dark");
    if (!client.connect(ip, port))
        throw Error("an error has been detected in Connect function");
    size_t nbPlayers = 1;

    std::cout << myPlayer.getModel() << std::endl;
    std::cout << myPlayer.getTexture() << std::endl;
    std::cout << myPlayer.getName() << std::endl;
    client.sendMessage(myPlayer.getFileName());
    client.sendMessage(myPlayer.getTexture());
    client.sendMessage(myPlayer.getName());

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
    for (size_t i = 0; i < nbPlayers; i++) {
        if (!client.receive())
            throw Error("receive error 3");
        if (client.type != Message)
            throw Error("model error");
        std::string model = client.message;
        if (!client.receive())
            throw Error("receive error 2");
        if (client.type != Message)
            throw Error("name error");
        std::string name = client.message;
        if (client.type != DataType::Position)
            throw Error("Position error");
        vector3du pos = client.pos;
            playerList.push_back(unique_ptr<Player>(new Player(window, model, name, world, pos)));
    }
    game(window, client, world, playerList);
}
