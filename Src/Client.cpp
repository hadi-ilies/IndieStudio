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
#include "Entity/PowerUp.hpp" //?
#include "FormattedSocket.hpp"

using namespace std;
using namespace irr;

bool startTurn = false; // tmp no global
bool endTurn = false; // tmp no global

enum PlayerAction {None, Up, Down, Left, Right, PutBomb};

void serverLoop(FormattedSocket *client)
{
    while (client->receive()) {
        if (client->type != StartTurn)
            throw ERROR("Thread failed");
        startTurn = true;
        while (startTurn && client->isConnected());
    }
    if (client->isConnected())
        throw ERROR("Thread failed");
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

static void execPlayerAction(PlayerAction &key, FormattedSocket &client, World &world, vector<unique_ptr<PowerUp>> &powerUpList, vector<unique_ptr<Player>> &playerList, const size_t &playerId)
{
    if (playerList[playerId]->getHp()) {
        if (key == PutBomb) {
            if (!client.sendPlayerPutBomb())
                throw ERROR("SendPlayerBomb error");
        }
        else if (key == Left) {
            if (!client.sendPlayerMove(vector2di(-1, 0)))
                throw ERROR("SendPlayer(-1, 0)");
        }
        else if (key == Right) {
            if (!client.sendPlayerMove(vector2di(1, 0)))
                throw ERROR("SendPlayerMov(1, 0)");
        }
        else if (key == Up) {
            if (!client.sendPlayerMove(vector2di(0, 1)))
                throw ERROR("SendPlayerMove(0, 1)");
        }
        else if (key == Down) {
            if (!client.sendPlayerMove(vector2di(0, -1)))
                throw ERROR("SendPlayerMove(0, -1)");
        }
        else if (!client.sendPlayerMove(vector2di(0, 0)))
            throw ERROR("SendPlayerMove(0, 0)");
    }
    else if (!client.sendPlayerMove(vector2di(0, 0)))
        throw ERROR("SendPlayerMove(0, 0)");
    for (unique_ptr<Player> &player: playerList) {
        if (!client.receive())
            throw ERROR("Client receiver");
        if (client.type == PlayerMove)
            player->move(client.direction);
        //check colision enenmies
        if (world.getBlock(player->getPosition()) && world.getBlock(player->getPosition())->getType() == "Fire")
            player->takeDamage();
        //check colision power up
        for (auto it = powerUpList.begin(); it != powerUpList.end();) {
            if (world.getBlock((*it)->getPosition()) && world.getBlock((*it)->getPosition())->getType() == "Fire")
                it = powerUpList.erase(it);
            else if (player->getPosition() == (*it)->getPosition()) {
                player->takePowerUp(**it);
                it = powerUpList.erase(it);
            }
            else
                it++;
        }
        if (client.type == PlayerPutBomb) //else if
            if (!player->putBomb())
                player->move(vector2di(0, 0));
        player->update();
    }
    world.update();
    startTurn = false;
    endTurn = true;
    key = None;
}

//NOTE : playerId not used there but it will be usefull

static void game(Window &window, FormattedSocket &client, World &world, vector<unique_ptr<PowerUp>> &powerUpList, vector<unique_ptr<Player>> &playerList, const size_t &playerId)
{
    thread loop(serverLoop, &client);
    PlayerAction key = None;

    while (window.isOpen() && client.isConnected()) {
        if (window.isKeyPressed(KEY_ESCAPE))
            window.close();
        getKey(window, key);
        if (startTurn)
            execPlayerAction(key, client, world, powerUpList, playerList, playerId);
        if (endTurn)
            if (turnHasFinished(playerList)) {
                if (!client.sendEndTurn())
                    throw ERROR("SendEndTurn failed");
                endTurn = false;
                //key = None; control Corentin dont remove it
            }
        window.display();
    }
    client.disconnect();
    startTurn = true; // for exit thread
    loop.join();
}

void client(Player &myPlayer, const sf::IpAddress &ip, const ushort &port) //put player in param
{
    FormattedSocket client;
    Window &window = Window::getInstance();
    //World myWorld("TODO"); // Todo put pointer on world constructor. this we allow us to put NULL in constructor
    //Player myPlayer("Bomberman", "Bob", NULL, vector3du(1, 1 ,1));
    //myPlayer.changeTexture("Default");
    if (!client.connect(ip, port))
        throw ERROR("An error has been detected in Connect function");
    size_t nbPlayer;

    std::cout << "FileName : " << myPlayer.getFileName() << std::endl;
    std::cout << "Model : " << myPlayer.getModel() << std::endl;
    std::cout << "Texture : " << myPlayer.getTexture() << std::endl;
    std::cout << "Name : " << myPlayer.getName() << std::endl;
    client.sendMessage(myPlayer.getFileName());
    client.sendMessage(myPlayer.getTexture());
    client.sendMessage(myPlayer.getName());

    if (!client.receive())
        throw ERROR("Receive error");
    if (client.type != Message)
        throw ERROR("Message error");
    cout << client.message << endl;
    World world("Resources/Map/" + client.message);
    vector<unique_ptr<Player>> playerList;

    //nb powerup
    if (!client.receive())
        throw ERROR("Receive bonus error");
    if (client.type != Number)
        throw ERROR("uin32 error");
    size_t nbPowerUp = client.number;
    //loop type position
    vector<unique_ptr<PowerUp>> powerUpList;
    cout << "nb power up : " << nbPowerUp << endl;
    for (size_t i = 0; i < nbPowerUp; i++) {
        //type
        if (!client.receive())
            throw ERROR("Message error");
        if (client.type != Message)
            throw ERROR("Type error");
        std::string powerUpType = client.message;
        //position
        if (!client.receive())
            throw ERROR("Message error");
        if (client.type != Position)
            throw ERROR("Position error");
        vector3du powerUpPosition = client.position;
        powerUpList.push_back(std::make_unique<PowerUp>(powerUpType, &world, powerUpPosition));
        powerUpList.back()->update();
    }
    if (!client.receive())
        throw ERROR("Receive error");
    if (client.type != Number)
        throw ERROR("uin32 error");
    nbPlayer = client.number;

    for (size_t i = 0; i < nbPlayer; i++) {
        if (!client.receive())
            throw ERROR("Receive error");
        if (client.type != Message)
            throw ERROR("Model error");;
        std::string fileName = client.message;

        if (!client.receive())
            throw ERROR("Receive error");
        if (client.type != Message)
            throw ERROR("Texture error");
        std::string texture = client.message;

        if (!client.receive())
            throw ERROR("Receive error");
        if (client.type != Message)
            throw ERROR("Name error");
        std::string name = client.message;

        if (!client.receive())
            throw ERROR("Receive error");
        if (client.type != Position)
            throw ERROR("Position error");
        vector3du position = client.position;

        playerList.push_back(std::make_unique<Player>(fileName, name, &world, position));
        playerList.back()->changeTexture(texture);
    }
    if (!client.receive())
        throw ERROR("Receive error");
    if (client.type != Number)
        throw ERROR("uint32 error");
    size_t playerId = client.number;

    game(window, client, world, powerUpList, playerList, playerId);
}
