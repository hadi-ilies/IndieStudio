/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Client.cpp
*/

#include <iostream> // ?
#include "Client.hpp"
#include "Error.hpp"

using namespace std;
using namespace irr;

void serverLoop(FormattedSocket *client, bool *startTurn, bool *endTurn)
{
    while (client->receive()) {
        if (client->type != StartTurn)
            throw ERROR("Thread failed");
        *startTurn = true;
        while (*startTurn && client->isConnected());
        while (*endTurn && client->isConnected());
    }
    if (client->isConnected())
        throw ERROR("Thread failed");
}

void addVictory()
{
    std::map<std::string, uint> ipScoreMap;

    // load
    ifstream file("Resources/Score");
    std::string line;
    smatch match;

    while (getline(file, line)) {
        if (line.empty())
            continue;
        if (regex_search(line, match, regex(R"(^((\d+\.){3}\d+) *: *(\d+)$)")))
            ipScoreMap[match[1]] = stoul(match[3]);
    }
    if (ipScoreMap.find(LOCAL_ADDRESS) == ipScoreMap.end())
        ipScoreMap[LOCAL_ADDRESS] = 0;
    ipScoreMap[LOCAL_ADDRESS]++;
    file.close();

    // save
    ofstream file2("Resources/Score", ifstream::trunc);

    for (const auto &ipScore : ipScoreMap)
        file2 << ipScore.first << " : " << ipScore.second << endl;
}

int playEndMusic(vector<unique_ptr<Player>> &playerList, const size_t &playerId, const PlayerType &playerType)
{
    size_t nbPlayerAlive = 0;
    bool isMe = false;

    for (size_t i = 0; i < playerList.size(); i++)
        if (playerList[i]->getHp()) {
            nbPlayerAlive++;
            if (i == playerId)
                isMe = true;
        }
    if (!nbPlayerAlive)
        return -1;
    if (nbPlayerAlive == 1) {
        if (playerType == Human)
            JukeBox::getInstance().pauseMusic("InGame");
        if (isMe) {
            if (playerType == Human) {
                addVictory();
                JukeBox::getInstance().playSound("Victory");
            }
            return 1;
        }
        else {
            if (playerType == Human)
                JukeBox::getInstance().playSound("Defeat");
            return -1;
        }
    }
    return 0;
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
    if (window.isKeyPressed(KEY_ESCAPE))
        key = Exit;
    else if (window.isKeyPressed(KEY_KEY_M))
        key = Save;
    else if (window.isKeyPressed(KEY_SPACE))
        key = PutBomb;
    else if (window.isKeyPressed(KEY_KEY_S) || window.isKeyPressed(KEY_DOWN))
        key = Down;
    else if (window.isKeyPressed(KEY_KEY_W) || window.isKeyPressed(KEY_KEY_Z) || window.isKeyPressed(KEY_UP))
        key = Up;
    else if (window.isKeyPressed(KEY_KEY_Q) || window.isKeyPressed(KEY_KEY_A) || window.isKeyPressed(KEY_LEFT))
        key = Left;
    else if (window.isKeyPressed(KEY_KEY_D) || window.isKeyPressed(KEY_RIGHT))
        key = Right;
    else
        return false;
    return true;
}

static int execPlayerAction(PlayerAction &key, FormattedSocket &client, const PlayerType &playerType, World &world, vector<unique_ptr<PowerUp>> &powerUpList, vector<unique_ptr<Player>> &playerList, const size_t &playerId, bool &startTurn, bool &endTurn)
{
    int returnValue = 0;

    if (key == Exit) {
        if (!client.sendPlayerDisconnect())
            throw ERROR("SendPlayerDisconnect");
    }
    else if (key == Save)
        world.save("Resources/Map/Game/Save");
    else if (playerList[playerId]->getHp()) {
        if (key == PutBomb) {
            if (!client.sendPlayerPutBomb())
                throw ERROR("SendPlayerBomb");
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
        //check colision enenmies
        if (world.getBlock(player->getPosition()) && world.getBlock(player->getPosition())->getType() == "Fire") {
            player->takeDamage();
            int tmp = playEndMusic(playerList, playerId, playerType);

            if (!returnValue)
                returnValue = tmp;
        }
        if (player->getHp()) {
            if (client.type == PlayerMove)
                player->move(client.direction);
            else if (client.type == PlayerPutBomb) {
                if (!player->putBomb())
                    player->move(vector2di(0, 0));
            }
            else if (client.type == PlayerDisconnect) {
                while (!player->takeDamage());
                int tmp = playEndMusic(playerList, playerId, playerType);

                if (!returnValue)
                    returnValue = tmp;
            }
        }
        //check colision power up
        for (auto it = powerUpList.begin(); it != powerUpList.end();) {
            /*if (world.getBlock((*it)->getPosition()) && world.getBlock((*it)->getPosition())->getType() == "Fire")
              it = powerUpList.erase(it);
              else*/
            if (player->getPosition() == (*it)->getPosition()) {
                player->takePowerUp(**it);
                it = powerUpList.erase(it);
            }
            else
                it++;
        }
    }
    for (unique_ptr<Player> &player: playerList)
        player->update();
    world.update();
    endTurn = true;
    startTurn = false;
    key = None;
    return returnValue;
}

///////////////////////////////////////////////////////////////////////////
////////////////////////           IA           ///////////////////////////
///////////////////////////////////////////////////////////////////////////

std::vector<std::vector<std::string>> getTabFromWorld(const World &world)
{
    std::vector<std::vector<std::string>> tab;

    tab.resize(world.getSize().X, std::vector<std::string>(world.getSize().Z, ""));
    for (uint i = 0; i < world.getSize().X; i++)
        for (uint j = 0; j < world.getSize().Z; j++)
            if (const Block *block = world.getBlock(vector3du(i, 1, j)))
                tab[i][j] = block->getType();
    return tab;
}

vector<vector2du> getPlayerPos(const vector<unique_ptr<Player>> &playerList)
{
    vector<vector2du> playerPos;

    for (const unique_ptr<Player> &player : playerList)
        playerPos.push_back(vector2du(player->getPosition().X, player->getPosition().Z));
    return playerPos;
}

vector<vector2du> getPowerUpPos(const vector<unique_ptr<PowerUp>> &powerUpList) // ?
{
    vector<vector2du> powerUpPos;

    for (const unique_ptr<PowerUp> &powerUp : powerUpList)
        powerUpPos.push_back(vector2du(powerUp->getPosition().X, powerUp->getPosition().Z));
    return powerUpPos;
}

std::list<Bomb*> getBombList(const vector<unique_ptr<Player>> &playerList)
{
    std::list<Bomb*> bombList;

    for (const unique_ptr<Player> &player : playerList)
        bombList.merge(std::list<Bomb*>(player->getBombList()));
    return bombList;
}

static void explode(std::vector<std::vector<std::string>> &tab, const vector2du &pos, const uint &power, const uint &tick)
{
    vector<vector2du> dirList = {
        vector2du(-1, 0),
        vector2du(1, 0),
        vector2du(0, -1),
        vector2du(0, 1)
    };

    tab[pos.X][pos.Y] = "";
    for (uint i = 0 ; i <= power ; i++)
        for (vector2du &j : dirList) {
            const vector2du newPos = pos + j * i;

            if (newPos.X >= tab.size() || newPos.Y >= tab[0].size())
                continue;
            if (tab[newPos.X][newPos.Y] == "Box") {
                //tab[newPos.X][newPos.Y] = ""; // add tick befor explode on Box
                j = vector2du(0, 0);
            }
            // TODO req explode (if tab[newPos.X][newPos.Y] == "^Bomb:\d+:\d+$")
            if (regex_search(tab[newPos.X][newPos.Y], regex(R"(^Fire:\d+$)"))) // TODO && Fire:tick > tick
                tab[newPos.X][newPos.Y] = "";
            if (tab[newPos.X][newPos.Y].empty())
                tab[newPos.X][newPos.Y] = "Fire:" + to_string(tick);
        }
}

static void simulBombExplode(std::vector<std::vector<std::string>> &tab)
{
    smatch match;

    for (size_t i = 0; i < tab.size(); i++)
        for (size_t j = 0; j < tab[i].size(); j++)
            if (regex_search(tab[i][j], match, regex(R"(^Bomb:(\d+):(\d+)$)"))) {
                uint power = stoul(match[1]);
                uint tick = stoul(match[2]);

                explode(tab, vector2du(i, j), power, tick);
            }
}

#define NOSET -1
#define WALL -2
#define FIRE -3

std::vector<std::vector<int>> getMoveTab(const std::vector<std::vector<std::string>> &tab, const vector2du &origin, const bool fireWall = true)
{
    std::vector<std::vector<int>> moveTab;
    bool spread = true;

    moveTab.resize(tab.size(), std::vector<int>(tab[0].size(), NOSET));
    for (size_t i = 0; i < tab.size(); i++)
        for (size_t j = 0; j < tab[i].size(); j++)
            if (tab[i][j] == "Ground" || tab[i][j] == "Wall" || tab[i][j] == "Box" || tab[i][j] == "Fire")
                moveTab[i][j] = WALL;
            else if (fireWall && regex_search(tab[i][j], regex(R"(^Fire:\d+$)")))
                moveTab[i][j] = WALL; // don't walk in fire
    moveTab[origin.X][origin.Y] = 0;
    for (int n = 0; spread; n++) {
        spread = false;
        for (size_t i = 1; i < moveTab.size() - 1; i++)
            for (size_t j = 1; j < moveTab[i].size() - 1; j++)
                if (moveTab[i][j] == n) {
                    spread = true;
                    if (moveTab[i][j - 1] == NOSET)
                        moveTab[i][j - 1] = n + 1;
                    if (moveTab[i][j + 1] == NOSET)
                        moveTab[i][j + 1] = n + 1;
                    if (moveTab[i - 1][j] == NOSET)
                        moveTab[i - 1][j] = n + 1;
                    if (moveTab[i + 1][j] == NOSET)
                        moveTab[i + 1][j] = n + 1;
                }
    }
    return moveTab;
}

static vector2du findCloser(const std::vector<std::vector<std::string>> &tab, const std::string &str, const vector2du &myPos, const bool fireWall = true)
{
    std::vector<std::vector<int>> moveTab = getMoveTab(tab, myPos, fireWall);
    vector2du less(0, 0);

    /*if (str != "")
        for (size_t i = 0; i < tab.size(); i++)
            for (size_t j = 0; j < tab[i].size(); j++)
                if (regex_search(tab[i][j], regex(R"(^Fire:\d+$)")))
                moveTab[i][j] = FIRE;*/

    for (size_t i = 0; i < tab.size(); i++)
        for (size_t j = 0; j < tab[i].size(); j++)
            if (tab[i][j] == str && moveTab[i][j] >= 0)
                if (less == vector2du(0, 0) || moveTab[i][j] < moveTab[less.X][less.Y])
                    less = vector2du(i, j);
    return less;
}

PlayerAction iaCorentin(const World &world, const vector<unique_ptr<PowerUp>> &powerUpList, const vector<unique_ptr<Player>> &playerList, const size_t &playerId)
{
    std::vector<std::vector<std::string>> tab = getTabFromWorld(world);
    vector<vector2du> playerPosList = getPlayerPos(playerList);
    vector2du &myPos = playerPosList[playerId];
    std::list<Bomb*> bombList = getBombList(playerList);

    for (const Bomb *bomb : bombList)
        if (bomb)
            tab[bomb->getPosition().X][bomb->getPosition().Z] = "Bomb:" + to_string(bomb->getPower()) + ":" + to_string(bomb->getTick());
    simulBombExplode(tab);
    if (regex_search(tab[myPos.X][myPos.Y], regex(R"(^Fire:\d+$)"))) {
        std::vector<std::vector<int>> moveTab = getMoveTab(tab, findCloser(tab, "", myPos, false), false);

        if (moveTab[myPos.X][myPos.Y - 1] >= 0 && moveTab[myPos.X][myPos.Y - 1] < moveTab[myPos.X][myPos.Y])
            return Down;
        if (moveTab[myPos.X][myPos.Y + 1] >= 0 && moveTab[myPos.X][myPos.Y + 1] < moveTab[myPos.X][myPos.Y])
            return Up;
        if (moveTab[myPos.X - 1][myPos.Y] >= 0 && moveTab[myPos.X - 1][myPos.Y] < moveTab[myPos.X][myPos.Y])
            return Left;
        if (moveTab[myPos.X + 1][myPos.Y] >= 0 && moveTab[myPos.X + 1][myPos.Y] < moveTab[myPos.X][myPos.Y])
            return Right;
    }
    for (const unique_ptr<PowerUp> &powerUp : powerUpList)
        if (powerUp && tab[powerUp->getPosition().X][powerUp->getPosition().Z] == "")
            tab[powerUp->getPosition().X][powerUp->getPosition().Z] = "PowerUp";//"PowerUp:" + powerUp->getType();
    vector2du CloserPowerUp = findCloser(tab, "PowerUp", myPos);

    /*cerr << "------- MAP -------" << endl;
    for (size_t i = 0; i < tab.size(); i++) {
        for (size_t j = 0; j < tab[i].size(); j++) {
            for (size_t n = tab[i][j].size(); n < 8; n++)
                cerr << " ";
            cerr << tab[i][j] << " ";
        }
        cerr << endl;
        }*/

    if (CloserPowerUp != vector2du(0, 0)) {
        std::vector<std::vector<int>> moveTab = getMoveTab(tab, CloserPowerUp);

        if (moveTab[myPos.X][myPos.Y - 1] >= 0 && moveTab[myPos.X][myPos.Y - 1] < moveTab[myPos.X][myPos.Y])
            return Down;
        if (moveTab[myPos.X][myPos.Y + 1] >= 0 && moveTab[myPos.X][myPos.Y + 1] < moveTab[myPos.X][myPos.Y])
            return Up;
        if (moveTab[myPos.X - 1][myPos.Y] >= 0 && moveTab[myPos.X - 1][myPos.Y] < moveTab[myPos.X][myPos.Y])
            return Left;
        if (moveTab[myPos.X + 1][myPos.Y] >= 0 && moveTab[myPos.X + 1][myPos.Y] < moveTab[myPos.X][myPos.Y])
            return Right;
    }
    return None;
}

///////////////////////////////////////////////////////////////////////////
////////////////////////           !IA          ///////////////////////////
///////////////////////////////////////////////////////////////////////////

static bool game(Window *window, FormattedSocket &client, const PlayerType &playerType, World &world, vector<unique_ptr<PowerUp>> &powerUpList, vector<unique_ptr<Player>> &playerList, const size_t &playerId)
{
    bool startTurn = false;
    bool endTurn = false;
    thread loop(serverLoop, &client, &startTurn, &endTurn);
    bool exit = false;
    PlayerAction key = None;
    int gameStatus = 0;

    if (playerType == Human) {
        JukeBox::getInstance().addMusic("InGame", "Resources/Music/IGMusic.ogg"); // TODO move in ctor
        JukeBox::getInstance().addSound("Victory", "Resources/Sound/Victory.ogg"); // TODO move in ctor
        JukeBox::getInstance().addSound("Defeat", "Resources/Sound/Defeat.ogg"); // TODO move in ctor // TODO add Defeat.ogg in Resources/Sound/
        JukeBox::getInstance().playMusic("InGame");
        if (window) {
            CameraMove cameraAnim(vector3df(world.getSize().X / 2.0, 20, world.getSize().Z / 2.0 - 10), vector3df(world.getSize().X / 2.0, 0, world.getSize().Z / 2.0), 1);

            cameraAnim.addPoint(vector3df(world.getSize().X / 2.0, 20, world.getSize().Z / 2.0 - 10));
            window->applyCameraMove(cameraAnim);
        }
    }
    while ((window && window->isOpen() && client.isConnected()) || !window && client.isConnected()) {
        if (playerType == Human)
            getKey(*window, key);
        if (startTurn) {
            if (playerType == IACorentin)
                key = iaCorentin(world, powerUpList, playerList, playerId);
            //else if (playerType == IAname) // for ohter IA
            if (gameStatus != 0)
                key = Exit;
            if (key == Exit)
                exit = true;
            int tmp = execPlayerAction(key, client, playerType, world, powerUpList, playerList, playerId, startTurn, endTurn);

            if (!gameStatus)
                gameStatus = tmp;
            if (exit) {
                cerr << "client disconnect" << endl;
                client.disconnect();
                break;
            }
        }
        if (endTurn)
            if (turnHasFinished(playerList)) {
                if (!client.sendEndTurn())
                    throw ERROR("SendEndTurn failed");
                endTurn = false;
                //key = None; control Corentin dont remove it
            }
        if (window)
            window->display();
    }
    if (playerType == Human)
        JukeBox::getInstance().pauseMusic("InGame");
    startTurn = true; // for exit thread
    loop.join();
    return gameStatus == 1;
}

bool client(Window *window, Player *myPlayer, const PlayerType &playerType, const sf::IpAddress &ip, const ushort &port)
{
    try {
        FormattedSocket client;

        if (!client.connect(ip, port))
            throw ERROR("An error has been detected in Connect function");
        size_t nbPlayer;

        client.sendMessage(myPlayer->getFileName());
        client.sendMessage(myPlayer->getTexture());
        client.sendMessage(myPlayer->getName());

        if (!client.receive())
            throw ERROR("Receive");
        if (client.type != Message)
            throw ERROR("Message");
        cerr << client.message << endl;
        World world(window, "Resources/Map/Game/" + client.message);
        vector<unique_ptr<Player>> playerList;

        //nb powerup
        if (!client.receive())
            throw ERROR("Receive bonus");
        if (client.type != Number)
            throw ERROR("uin32");
        size_t nbPowerUp = client.number;
        //loop type position
        vector<unique_ptr<PowerUp>> powerUpList;
        cerr << "nb power up : " << nbPowerUp << endl;
        for (size_t i = 0; i < nbPowerUp; i++) {
            //type
            if (!client.receive())
                throw ERROR("Message");
            if (client.type != Message)
                throw ERROR("Type");
            std::string powerUpType = client.message;
            //position
            if (!client.receive())
                throw ERROR("Message");
            if (client.type != Position)
                throw ERROR("Position");
            vector3du powerUpPosition = client.position;
            powerUpList.push_back(std::make_unique<PowerUp>(window, powerUpType, &world, powerUpPosition));
            powerUpList.back()->update();
        }
        if (!client.receive())
            throw ERROR("Receive");
        if (client.type != Number)
            throw ERROR("uin32");
        nbPlayer = client.number;

        cerr << "nb player : " << nbPlayer << endl;
        for (size_t i = 0; i < nbPlayer; i++) {
            if (!client.receive())
                throw ERROR("Receive");
            if (client.type != Message)
                throw ERROR("Model");
            std::string fileName = client.message;

            if (!client.receive())
                throw ERROR("Receive");
            if (client.type != Message)
                throw ERROR("Texture");
            std::string texture = client.message;

            if (!client.receive())
                throw ERROR("Receive");
            if (client.type != Message)
                throw ERROR("Name");
            std::string name = client.message;

            if (!client.receive())
                throw ERROR("Receive");
            if (client.type != Position)
                throw ERROR("Position");
            vector3du position = client.position;

            playerList.push_back(std::make_unique<Player>(window, fileName, name, &world, position));
            playerList.back()->changeTexture(texture);
        }
        if (!client.receive())
            throw ERROR("Receive");
        if (client.type != Number)
            throw ERROR("uint32");
        size_t playerId = client.number;

        cerr << "start game" << endl;
        return game(window, client, playerType, world, powerUpList, playerList, playerId);
    }
    catch (const Error &e) {
        std::cerr << "[" << e.where() << "]" << std::endl;
        std::cerr << "\t" << e.what() << std::endl;
    }
    catch (const exception &e) {
        std::cerr << "EXCEPTION : " << e.what() << std::endl;
    }
    return false;
}
