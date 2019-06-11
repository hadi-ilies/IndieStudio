/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** UserInterface
*/

#include "JukeBox.hpp"
#include "Error.hpp"

/*
 *   Constructors // Destructors
 */
UserInterface::UserInterface() : menu(nullptr), camera(nullptr), lock(false),
                                 myPlayer(new Player("Bomberman", "Bob", nullptr, vector3du(0, 0, 0))) {

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
    Menu *modelMenu = new Menu("Player", vector3df(20, 500, 0), vector3df(10, 500, 0));
    Menu *textureMenu = new Menu("Texture", vector3df(20, 4000, 0), vector3df(10, 4000, 0));

    soloMenu->addWheel(vector3df(0, 50, 0), 10, { "Stage", "Play", "Back" }); //tmp
    StageMenu->addWheel(vector3df(0, 100, 0), 10, {{ "Model1", "Bomberman", "Dark" },
                                                   { "Model2", "Bomberman", "Dark" },
                                                   { "Model3", "Bomberman", "Dark" }}); //tmp
    multiPlayerMenu->addWheel(vector3df(50, 50, 0), 10, { "Server", "Client", "Back" }); //tmp
    settingsMenu->addWheel(vector3df(0, -100, 0), 10, { "Sound", "Resolution", "Back" }); //tmp
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
    soloMenu->linkMenu("Back", menu);
    multiPlayerMenu->linkMenu("Back", menu);
    settingsMenu->linkMenu("Back", menu);
}

Menu *UserInterface::createMenuBomberman() {
    float radius = 10;
    menu = new Menu("Main", vector3df(20, 0, 0), vector3df(10, 0, 0));

    menu->addWheel(vector3df(0, 0, 0), radius, { "Solo", "Multi", "Settings", "Player", "Exit" });
    linkButtonToMenu();
    return menu;
}

void UserInterface::create() //tmp
{
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
            setBackGround("BackgroundMenu.jpg");
            JukeBox::getInstance().pauseMusic("demo");
           return true;
        }
        Window::getInstance().display();
    }
    return false;
}

void client(Player &myPlayer, const sf::IpAddress &ip, const ushort &port);
void server(const ushort &port, const std::string &worldFileName, const size_t &nbPlayer);

void UserInterface::run(const vector3df &cameraPos, const vector3df &cameraTarget) {
    camera = Window::getInstance().getCameraSceneNode(cameraPos, cameraTarget);

    while (Window::getInstance().isOpen()) {
        if (menu->getKey() && menu->getName() == "Player")
            myPlayer = new Player(menu->getCurrentButtonModel(), "BOB", nullptr, vector3du(1, 1, 1));
        else if (menu->getKey() && menu->getName() == "Texture")
            myPlayer->changeTexture(menu->getCurrentButtonTexture());
        if (menu->getKey()) {
            if (!lock) {
                if (!menu->getMenu() && menu->getCurrentButtonName() == "Exit")
                    Window::getInstance().close();
                if (!menu->getMenu() && menu->getCurrentButtonName() == "Play") {
                     uint port = 8080;
                     std::thread my_server(server, port, "Default", 1); //tmp remove window inside this func
                     sleep(10);
                     client(*myPlayer, sf::IpAddress("127.0.0.1"), port); //tmp // send player in funtion*/
                }
                if (menu->getMenu()) {
                    CameraMove cameraAnim(menu->getPosition(), menu->getMenu()->getTargetPosition(), 1);
                    cameraAnim.addPoint(menu->getMenu()->getPosition());
                    Window::getInstance().applyCameraMove(cameraAnim);
                    menu->setPrevMenu(menu);
                    menu = menu->getMenu();
                }
                lock = true;
            }
        } else
            lock = false;
        Window::getInstance().display();
    }
}
