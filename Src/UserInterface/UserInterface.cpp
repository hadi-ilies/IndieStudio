/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** UserInterface
*/

#include "UserInterface/UserInterface.hpp"
#include "Error.hpp"

/*
 *   Constructors // Destructors
 */
UserInterface::UserInterface() : menu(nullptr), prevMenu(nullptr), camera(nullptr), interfaceMusics(40), interfaceSounds(100), lock(false),
                                 myPlayer(new Player("Bomberman", "Bob", nullptr, vector3du(0, 0, 0)))
{
}

UserInterface::~UserInterface() = default;

/*
 *   Getters // Setters
 */

/*
 *   Methods
 */
//todo create factory menu
void UserInterface::linkButtonToMenu() {
    Menu *soloMenu = new Menu("Solo", vector3df(20, 50, 0), vector3df(10, 50, 0));
    Menu *StageMenu = new Menu("Stage", vector3df(20, 100, 0), vector3df(10, 100, 0));
    Menu *multiPlayerMenu = new Menu("Multiplayer", vector3df(70, 50, 0), vector3df(60, 50, 0));
    Menu *settingsMenu = new Menu("Settings", vector3df(20, -100, 0), vector3df(10, -100, 0));
    Menu *soundMenu = new Menu("Sound", vector3df(20, -400, 0), vector3df(10, -400, 0));
    Menu *musicMenu = new Menu("Music", vector3df(20, -800, 0), vector3df(10, -800, 0));
    Menu *modelMenu = new Menu("Player", vector3df(20, 500, 0), vector3df(10, 500, 0));
    Menu *textureMenu = new Menu("Texture", vector3df(20, 4000, 0), vector3df(10, 4000, 0));

    soloMenu->addWheel(vector3df(0, 50, 0), 10, { "Stage", "Play", "Back" }); //tmp
    StageMenu->addWheel(vector3df(0, 100, 0), 10, {{ "Model1", "Bomberman", "Dark" },
                                                   { "Model2", "Bomberman", "Dark" },
                                                   { "Model3", "Bomberman", "Dark" }}); //tmp
    multiPlayerMenu->addWheel(vector3df(50, 50, 0), 10, { "Server", "Client", "Back" }); //tmp
    settingsMenu->addWheel(vector3df(0, -100, 0), 10, { "Music", "Sound", "Resolution", "Back" }); //tmp
    soundMenu->addWheel(vector3df(0, -400, 0), 10, { "More", "Less", "Back" }); //tmp
    musicMenu->addWheel(vector3df(0, -800, 0), 10, { "More", "Less", "Back" }); //tmp
    modelMenu->addWheel(vector3df(0, 500, 0), 10, {{ "Model1", "Bomberman", "" },
                                                   { "Model2", "Bomberman", "" },
                                                   { "Model3", "Bomberman", "" }}); //tmp
    textureMenu->addWheel(vector3df(0, 4000, 0), 10, {{ "Texture1", "Bomberman", "Test2" },
                                                      { "Texture2", "Bomberman", "Dark" },
                                                      { "Texture3", "Bomberman", "Default" }}); //tmp

    soloMenu->linkMenu(StageMenu->getName(), StageMenu);
    menu->linkMenu(soloMenu->getName(), soloMenu);
    menu->linkMenu(multiPlayerMenu->getName(), multiPlayerMenu);
    menu->linkMenu(settingsMenu->getName(), settingsMenu);
    modelMenu->linkMenu("Model1", textureMenu);
    modelMenu->linkMenu("Model2", textureMenu);
    modelMenu->linkMenu("Model3", textureMenu);
    textureMenu->linkMenu("Texture1", menu);
    textureMenu->linkMenu("Texture2", menu);
    textureMenu->linkMenu("Texture3", menu);
    menu->linkMenu(modelMenu->getName(), modelMenu);
    settingsMenu->linkMenu(soundMenu->getName(), soundMenu);
    settingsMenu->linkMenu(musicMenu->getName(), musicMenu);
    soloMenu->linkMenu("Back", menu);
    multiPlayerMenu->linkMenu("Back", menu);
    settingsMenu->linkMenu("Back", menu);
    soundMenu->linkMenu("Back", settingsMenu);
    musicMenu->linkMenu("Back", settingsMenu);
}

Menu *UserInterface::createMenuBomberman() {
    float radius = 10;

    menu = new Menu("Main", vector3df(20, 0, 0), vector3df(10, 0, 0));
    menu->addWheel(vector3df(0, 0, 0), radius, { "Solo", "Multi", "Settings", "Player", "Exit" });
    linkButtonToMenu();
    return menu;
}

void UserInterface::create(const std::string &backgroundMusic) //tmp
{
    JukeBox::getInstance().addMusic("Menu", "Resources/Music/" + backgroundMusic);
    JukeBox::getInstance().addSound("Back", "Resources/Sound/Off.ogg");
    JukeBox::getInstance().addSound("Enter", "Resources/Sound/Transition.ogg");
    JukeBox::getInstance().addSound("Switch", "Resources/Sound/On.ogg");

    JukeBox::getInstance().setVolumeMusic(interfaceMusics);
    JukeBox::getInstance().setVolumeSound(interfaceSounds);

    menu = createMenuBomberman();
}

void UserInterface::setBackGround(const std::string &backGround) {
    Window::getInstance().changeSkybox("Resources/Texture/" + backGround);
}

bool UserInterface::demo() {
    CameraMove cameraFirstMove;
    CameraMove cameraSecondMove;
    World world("Resources/Map/DemoWithoutEdge");
    ISceneNodeAnimator *animation;

    setBackGround("BackgroundDemo.jpg");
    cameraFirstMove.generateFirstMove();
    cameraSecondMove.generateDemoSecondMove();
    cameraSecondMove.setLoop(true);
    animation = Window::getInstance().applyCameraMove(cameraFirstMove);

    Window::getInstance().setDebugMode(true); // tmp
    JukeBox::getInstance().addMusic("demo", "Resources/Music/DemoMusic.ogg");
    JukeBox::getInstance().playMusic("demo");

    while (Window::getInstance().isOpen()) {
        if (animation && animation->hasFinished()) {
            animation = Window::getInstance().applyCameraMove(cameraSecondMove);
        }
        if (Window::getInstance().isKeyPressed(KEY_KEY_P)) {
            JukeBox::getInstance().pauseMusic("demo");
           return true;
        }
        Window::getInstance().display();
    }
    return false;
}

void client(Player &myPlayer, const sf::IpAddress &ip, const ushort &port);
void server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer);

void UserInterface::checkVolume()
{
    if (menu->getCurrentButtonName() == "More" && menu->getName() == "Sound")
        JukeBox::getInstance().setVolumeSound(interfaceSounds == 100 ? 100 : ++interfaceSounds);
    else if (menu->getCurrentButtonName() == "More" && menu->getName() == "Music")
        JukeBox::getInstance().setVolumeMusic(interfaceMusics == 100 ? 100 : ++interfaceMusics);
    else if (menu->getCurrentButtonName() == "Less" && menu->getName() == "Sound")
        JukeBox::getInstance().setVolumeSound(interfaceSounds == 0 ? 0 : --interfaceSounds);
    else if (menu->getCurrentButtonName() == "Less" && menu->getName() == "Music")
        JukeBox::getInstance().setVolumeMusic(interfaceMusics == 0 ? 0 : --interfaceMusics);
}

void UserInterface::run(const vector3df &cameraPos, const vector3df &cameraTarget) {
    camera = Window::getInstance().getCameraSceneNode(cameraPos, cameraTarget);
    JukeBox::getInstance().playMusic("Menu");

    while (Window::getInstance().isOpen()) {
        if (menu->getKey() && menu->getName() == "Player")
            myPlayer = new Player(menu->getCurrentButtonModel(), "BOB", nullptr, vector3du(1, 1, 1));
        else if (menu->getKey() && menu->getName() == "Texture")
            myPlayer->changeTexture(menu->getCurrentButtonTexture());
        if (menu->getKey()) {
            if (!lock) {
                checkVolume();
                if(menu->getCurrentButtonName() == "Back")
                    JukeBox::getInstance().playSound("Back");
                if(!menu->getMenu() && menu->getCurrentButtonName() == "Exit")
                    Window::getInstance().close();
                else if (!menu->getMenu() && menu->getCurrentButtonName() == "Play") {
                     //uint port = 8080;
                     //std::thread my_server(server, port, "Default", 1); //tmp remove window inside this func
                     //sleep(10);
                     //client(*myPlayer, sf::IpAddress("127.0.0.1"), port); //tmp // send player in funtion*/
                }
                else if (menu->getMenu()) {
                    CameraMove cameraAnim(menu->getPosition(), menu->getMenu()->getTargetPosition(), 1);
                    cameraAnim.addPoint(menu->getMenu()->getPosition());
                    Window::getInstance().applyCameraMove(cameraAnim);
                    //menu->setPrevMenu(menu);
                    prevMenu = menu;
                    menu = menu->getMenu();
                }
                lock = true;
            }
        } else
            lock = false;
        Window::getInstance().display();
    }
}
