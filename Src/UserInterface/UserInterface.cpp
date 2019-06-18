/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** UserInterface
*/

#include "UserInterface/UserInterface.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Error.hpp"

/*
 *   Constructors // Destructors
 */
UserInterface::UserInterface()
    : irrFontBuffer(FONT_TYPE, GENERATE_FONT),
      window("Bomberman", dimension2d<u32>(1920, 1080), false), menu(nullptr),
      prevMenu(nullptr), camera(nullptr), interfaceMusics(40), interfaceSounds(100),
      ipDisplayerMenu(nullptr),
      soundMenu (nullptr),
      musicMenu (nullptr),
      lock(false),
      myPlayer(new Player(nullptr, "Bomberman", USERNAME, nullptr, vector3du(0, 0, 0))),
      mapGame("Default") {
    //create sounds
    JukeBox::getInstance().addMusic("Menu", "Resources/Music/MenuMusic.ogg");
    JukeBox::getInstance().addSound("Back", "Resources/Sound/buttonClick.ogg");
    JukeBox::getInstance().addSound("Enter", "Resources/Sound/Transition.ogg");
    JukeBox::getInstance().addSound("Switch", "Resources/Sound/buttonClick.ogg");

    //create musics
    JukeBox::getInstance().setVolumeMusic(interfaceMusics);
    JukeBox::getInstance().setVolumeSound(interfaceSounds);
}

UserInterface::~UserInterface() = default; // TODO in hpp

/*
 *   Methods
 */
//todo create factory menu

void UserInterface::linkButtonToMenu() {
    //create menus
    Menu *soloMenu = new Menu(window, irrFontBuffer, "Solo", vector3df(20, 53, 0), vector3df(10, 50, 0));
    Menu *multiPlayerMenu = new Menu(window, irrFontBuffer, "Multi", vector3df(70, 53, 0), vector3df(60, 50, 0));
    Menu *nbPlayerMenu = new Menu(window, irrFontBuffer, "nbPlayer", vector3df(130, 53, 0), vector3df(120, 50, 0));
    Menu *ipMenu = new Menu(window, irrFontBuffer, "ip", vector3df(-90, 53, 0), vector3df(-100, 50, 0));
    Menu *settingsMenu = new Menu(window, irrFontBuffer, "Settings", vector3df(20, -97, 0), vector3df(10, -100, 0));
    Menu *soundMenu = new Menu(window, irrFontBuffer, "Sound", vector3df(20, -397, 0), vector3df(10, -400, 0));
    Menu *musicMenu = new Menu(window, irrFontBuffer, "Music", vector3df(20, -797, 0), vector3df(10, -800, 0));
    Menu *modelMenu = new Menu(window, irrFontBuffer, "Player", vector3df(20, 503, 0), vector3df(10, 500, 0));

    //create Wheels
    soloMenu->addWheel(vector3df(0, 50, 0), 10, { "Stage", "Play", "Back" }); //tmp
    multiPlayerMenu->addWheel(vector3df(50, 50, 0), 10, { "Host", "Join", "Stage", "Back" }); //tmp
    nbPlayerMenu->addWheel(vector3df(110, 50, 0), 10, { "2", "3", "4", "5", "6", "7", "8", "9", "Back" }); //tmp
    ipMenu->addWheel(vector3df(-110, 50, 0), 10,
                     { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "<==", "Back", "SelectIp" }); //tmp
    settingsMenu->addWheel(vector3df(0, -100, 0), 10, { "Music", "Sound", "Back" }); //tmp
    soundMenu->addWheel(vector3df(0, -400, 0), 10, { "More", "Less", "Back" }); //tmp
    musicMenu->addWheel(vector3df(0, -800, 0), 10, { "More", "Less", "Back" }); //tmp
    modelMenu->addWheel(vector3df(5, 500, 0), 10, {{ "Model1", "Bomberman", "Default" },
                                                   { "Model2", "Sydney", "Default" },
                                                   { "Model3", "Fairy", "Default" }}); //tmp

    //link buttons
    menu->linkMenu(soloMenu->getName(), soloMenu);
    menu->linkMenu(multiPlayerMenu->getName(), multiPlayerMenu);
    multiPlayerMenu->linkMenu("Host", nbPlayerMenu);
    multiPlayerMenu->linkMenu("Join", ipMenu);
    menu->linkMenu(settingsMenu->getName(), settingsMenu);
    menu->linkMenu(modelMenu->getName(), modelMenu);
    settingsMenu->linkMenu(soundMenu->getName(), soundMenu);
    settingsMenu->linkMenu(musicMenu->getName(), musicMenu);

    //link back buttons
    soloMenu->linkMenu("Back", menu);
    multiPlayerMenu->linkMenu("Back", menu);
    settingsMenu->linkMenu("Back", menu);
    soundMenu->linkMenu("Back", settingsMenu);
    musicMenu->linkMenu("Back", settingsMenu);
    nbPlayerMenu->linkMenu("Back", multiPlayerMenu);
    ipMenu->linkMenu("Back", multiPlayerMenu);
}

Menu *UserInterface::createMenuBomberman() {
    const float radius = 10;

    menu = new Menu(window, irrFontBuffer, "Main", vector3df(20, -3, 0), vector3df(10, -5, 0));
    menu->addWheel(vector3df(5, -5, 0), radius, { "Solo", "Multi", "Settings", "Player", "Exit" });
    linkButtonToMenu();
    return menu;
}

void UserInterface::create() {
    //create menu
    menu = createMenuBomberman();
    //set a save of the root menu
    mainMenu = menu;
}

void UserInterface::setBackGround(const std::string &backGround) {
    window.changeSkybox("Resources/Texture/" + backGround);
}

bool UserInterface::demo() {
    CameraMove cameraFirstMove;
    CameraMove cameraSecondMove;
    World world(&window, "Resources/Map/DemoWithoutEdge");
    ISceneNodeAnimator *animation;

    setBackGround("BackgroundDemo.jpg");
    cameraFirstMove.generateFirstMove();
    cameraSecondMove.generateDemoSecondMove();
    cameraSecondMove.setLoop(true);
    animation = window.applyCameraMove(cameraFirstMove);

    window.setDebugMode(true); // tmp
    JukeBox::getInstance().addMusic("demo", "Resources/Music/DemoMusic.ogg");
    JukeBox::getInstance().playMusic("demo");

    while (window.isOpen()) {
        if (animation && animation->hasFinished()) {
            animation = window.applyCameraMove(cameraSecondMove);
        }
        if (window.isKeyPressed(KEY_KEY_P)) {
            JukeBox::getInstance().pauseMusic("demo");
            return true;
        }
        window.display();
    }
    return false;
}

void UserInterface::checkVolume() {
    bool musicLock = true;
    bool soundLock = true;

    if (menu->getCurrentButtonName() == "More" && menu->getName() == "Sound") {
        JukeBox::getInstance().setVolumeSound(interfaceSounds >= 100 ? 100 : interfaceSounds += 5);
        soundLock = false;
    } else if (menu->getCurrentButtonName() == "More" && menu->getName() == "Music") {
        JukeBox::getInstance().setVolumeMusic(interfaceMusics >= 100 ? 100 : interfaceMusics += 5);
        musicLock = false;
    }
    else if (menu->getCurrentButtonName() == "Less" && menu->getName() == "Sound") {
        JukeBox::getInstance().setVolumeSound(interfaceSounds <= 0 ? 0 : interfaceSounds -= 5);
        soundLock = false;
    }
    else if (menu->getCurrentButtonName() == "Less" && menu->getName() == "Music") {
        JukeBox::getInstance().setVolumeMusic(interfaceMusics <= 0 ? 0 : interfaceMusics -= 5);
        musicLock = false;
    }
    if (!musicLock) {
        delete musicMenu;
        musicMenu = new Menu (window, irrFontBuffer, "musicDisplayer", vector3df(20, -797, 0), vector3df(10, -800, 0));
        musicMenu->addWheel(vector3df(0, -795, 0), 10, {"", std::to_string((int)interfaceMusics) + "%"});
    }
    if (!soundLock) {
        delete soundMenu;
        soundMenu = new Menu (window, irrFontBuffer, "musicDisplayer", vector3df(20, -397, 0), vector3df(10, -400, 0));
        soundMenu->addWheel(vector3df(0, -395, 0), 10, {"", std::to_string((int)interfaceSounds) + "%"});
    }
}

void UserInterface::createTexture() {
    int i = 0;
    Menu *textureMenu = new Menu(window, irrFontBuffer, "texture", vector3df(20, 4003, 0), vector3df(10, 4000, 0));
    std::vector<Wheel::ParamButton> textures;

    for (std::string &texture: globpp("Resources/Entity/" + myPlayer->getFileName() + "/Texture")) {
        smatch match;
        if (regex_search(texture, match, regex(R"(([\w\d]+)\.png$)"))) {
            std::string buttonName = (std::string) "texture" + std::to_string(++i);
            textures.push_back({ buttonName, myPlayer->getFileName(), match[1] });
            textureMenu->linkMenu(buttonName, mainMenu);
        }
    }
    textureMenu->addWheel(vector3df(5, 4000, 0), 10, textures);
    menu->linkMenu(menu->getCurrentButtonName(), textureMenu);
}


void UserInterface::createMaps() {
    Menu *stageMenu = new Menu(window, irrFontBuffer, "stage", vector3df(20, 103, 0), vector3df(10, 100, 0));
    std::vector<std::string> maps;

    for (std::string &map: globpp("Resources/Map/Game")) {
        smatch match;
        if (regex_search(map, match, regex(R"(([\w\d]+)$)"))) {
            std::string filename = match[1];
            maps.push_back(filename);
            stageMenu->linkMenu(filename, menu);
        }
    }
    stageMenu->addWheel(vector3df(0, 100, 0), 10, maps);
    menu->linkMenu(menu->getCurrentButtonName(), stageMenu);
}

void UserInterface::checkPlayerFeatures() {
    if (menu->getKey() && menu->getName() == "Player") {
        delete myPlayer;
        myPlayer = new Player(&window, menu->getCurrentButtonModel(), USERNAME, nullptr, vector3du(1, 1, 1));
        createTexture();
    } else if (menu->getKey() && menu->getName() == "texture")
        myPlayer->changeTexture(menu->getCurrentButtonTexture());
    else if (menu->getKey() && menu->getCurrentButtonName() == "Stage") //Warning if create another button stage that do not do the same work its will be an issue
        createMaps();
    else if (menu->getKey() && menu->getName() == "stage")
        mapGame = menu->getCurrentButtonName();
}

bool UserInterface::isIpV4Address(const std::string &ip) {
    struct sockaddr_in sa;

    return inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr)) != 0;
}

void UserInterface::switchStatusMenu(const std::string &status)
{
    Menu *statusMenu = new Menu(window, irrFontBuffer, status, vector3df(-480, -500, 0), vector3df(-490, -500, 0));

    statusMenu->addWheel(vector3df(-500, -500, 0), 10, {status}); //tmp
    statusMenu->linkMenu(status, mainMenu);
    menu->linkMenu(menu->getCurrentButtonName(), statusMenu);
}

void UserInterface::ipDisplayer(std::string &ipServer)
{
    ipDisplayerMenu = new Menu (window, irrFontBuffer, "ipDisplayer", vector3df(-90, 53, 0), vector3df(-100, 50, 0));
    ipDisplayerMenu->addWheel(vector3df(-101, 53, 0), 10, {"", ipServer});
}

void UserInterface::selectIp(std::string &ipServer)
{
    if (menu->getCurrentButtonName() == "SelectIp" && isIpV4Address(ipServer)) {
        JukeBox::getInstance().pauseMusic("Menu");
        if (client(&window, myPlayer, Human, sf::IpAddress(ipServer), SERVER_PORT))
            switchStatusMenu("Victory");
        else
            switchStatusMenu("Defeat");
        JukeBox::getInstance().playMusic("Menu");
    changeScene(menu->getPosition(), menu->getMenu()->getPosition(), menu->getMenu()->getTargetPosition());
    switchMenu();
    } else if (menu->getCurrentButtonName() == "<==" && !ipServer.empty()) {
        delete ipDisplayerMenu;
        ipServer.pop_back();
        ipDisplayer(ipServer);
    } else if (ipServer.size() < 15) {
        if (menu->getCurrentButtonName() == "." || (menu->getCurrentButtonName() != "Back" && menu->getCurrentButtonName() != "SelectIp" && menu->getCurrentButtonName() != "<==")) {
            delete ipDisplayerMenu;
            ipServer += menu->getCurrentButtonName();
            ipDisplayer(ipServer);
        }
    }
}

void UserInterface::changeScene(const vector3df &cameraPos, const vector3df &cameraDestPos, const vector3df &cameraTarget) {
    CameraMove cameraAnim(cameraPos, cameraTarget, 1);
    cameraAnim.addPoint(cameraDestPos);
    window.applyCameraMove(cameraAnim);
}

void UserInterface::playGame(const std::string &targetIp, const size_t &nbPlayer, const size_t &port, const bool soloMode)
{
    std::vector<std::unique_ptr<std::thread>> myIaList;
    std::thread myServer(server, port, mapGame, nbPlayer);
    bool victory;
    sleep(1); // ? make a pause to let time to the server to load

    if (soloMode)
        for (size_t i = 1; i < nbPlayer; i++) {
            Player *aiPlayer = new Player(&window, "Bomberman", "Bob", nullptr, vector3du(0, 0, 0));

            aiPlayer->changeTexture("RANDOM");
            myIaList.push_back(std::move(std::make_unique<std::thread>(client, nullptr, aiPlayer, IACorentin, sf::IpAddress(targetIp), port)));
            sleep(1); // tmp // TODO supr
            delete aiPlayer;
        }
    victory = client(&window, myPlayer, Human, sf::IpAddress(targetIp), port);
    for (auto &myIa : myIaList)
        myIa->join();
    myServer.join();
    JukeBox::getInstance().pauseMusic("Menu");
    if (victory)
        switchStatusMenu("Victory");
    else
        switchStatusMenu("Defeat");
    changeScene(menu->getPosition(), menu->getMenu()->getPosition(), menu->getMenu()->getTargetPosition());
    JukeBox::getInstance().playMusic("Menu");
    switchMenu();
}

void UserInterface::switchMenu() {
    changeScene(menu->getPosition(), menu->getMenu()->getPosition(), menu->getMenu()->getTargetPosition());
    prevMenu = menu;
    Menu *tmpMenu = menu->getMenu();
    if (menu->getName() == "texture" || menu->getName() == "stage" || menu->getName() == "Defeat" || menu->getName() == "Victory")
        delete menu;
    menu = tmpMenu;
}


void UserInterface::run(const vector3df &cameraPos, const vector3df &cameraTarget) {
    camera = window.getCameraSceneNode(cameraPos, cameraTarget);
    JukeBox::getInstance().playMusic("Menu");
    std::string ipServer;

    while (window.isOpen()) {
        if (menu->getKey()) {
            if (!lock) {
                checkVolume();
                checkPlayerFeatures();
                if (menu->getCurrentButtonName() == "Back") {
                    JukeBox::getInstance().playSound("Back");
                    switchMenu();
                    lock = true;
                    continue;
                }
                if (!menu->getMenu() && menu->getCurrentButtonName() == "Exit")
                    window.close();
                else if (menu->getCurrentButtonName() == "Play")
                    playGame(LOCALHOST, SOLO, SERVER_PORT, true);
                else if (menu->getName() == "ip")
                    selectIp(ipServer);
                else if (menu->getName() == "nbPlayer")
                    playGame(LOCALHOST, std::stoi(menu->getCurrentButtonName()), SERVER_PORT, false);
                else if (menu->getMenu())
                    switchMenu();
                lock = true;
            }
        } else
            lock = false;
        window.display();
    }
}
