/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** UserInterface
*/

#include "UserInterface/UserInterface.hpp"
#include "Error.hpp"

//background.png
UserInterface::UserInterface(Window *window)
    : window (window), menu(NULL), camera (NULL), lock(false), myPlayer(new Player(NULL, "Bomberman", "Bob", NULL, vector3du(0, 0 ,0)))
{
    if (!window)
        throw Error("You can't create a userInterface without Window !");
}

UserInterface::~UserInterface()
{
}

//todo create factory menu
void UserInterface::linkButtonToMenu(Window *window, Menu *menu)
{
    Menu *soloMenu = new Menu(window, "Solo", vector3df(20, 50, 0), vector3df(10, 50, 0));
    Menu *StageMenu = new Menu(window, "Stage", vector3df(20, 100, 0), vector3df(10, 100, 0));
    Menu *multiPlayerMenu = new Menu(window, "Multiplayer", vector3df(70, 50, 0), vector3df(60, 50, 0));
    Menu *settingsMenu = new Menu(window, "Settings", vector3df(20, -100, 0), vector3df(10, -100, 0));
    Menu *modelMenu = new Menu(window, "Player", vector3df(20, 500, 0), vector3df(10, 500, 0));
    Menu *textureMenu = new Menu(window, "Texture", vector3df(20, 4000, 0), vector3df(10, 4000, 0));

    soloMenu->addWheel(vector3df(0, 50, 0), 10, {{"Stage", "Bomberman", "Default"}, {"Play", "Bomberman", "Dark"}, {"Back", "Bomberman", "Dark"}}); //tmp
    StageMenu->addWheel(vector3df(0, 100, 0), 10, {{"Model1", "Bomberman", "Dark"}, {"Model2", "Bomberman", "Dark"}, {"Model3", "Bomberman", "Dark"}}); //tmp
    multiPlayerMenu->addWheel(vector3df(50, 50, 0), 10, {{"Server", "Bomberman", "Default"}, {"Client", "Bomberman", "Default"}, {"Back", "Bomberman", "Default"}}); //tmp
    settingsMenu->addWheel(vector3df(0, -100, 0), 10, {{"Sound", "Bomberman", "Default"}, {"Resolution", "Bomberman", "Dark"}, {"Back", "Bomberman", "Dark"}}); //tmp
    modelMenu->addWheel(vector3df(0, 500, 0), 10, {{"Model1", "Bomberman", "Dark"}, {"Model2", "Bomberman", "Dark"}, {"Model3", "Bomberman", "Texture"}}); //tmp
    textureMenu->addWheel(vector3df(0, 4000, 0), 10, {{"Texture1", "Bomberman", "Dark"}, {"Texture2", "Bomberman", "Dark"}, {"Texture3", "Bomberman", "Texture"}}); //tmp

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

Menu *UserInterface::createMenuBomberman(Window *window)
{
    float radius = 10;
    Menu *menu = new Menu(window, "Main", vector3df(20, 0, 0), vector3df(10, 0, 0));

    menu->addWheel(vector3df(0, 0, 0), radius, {{"Solo", "Bomberman", "Dark"}, {"Multiplayer", "Bomberman", "Dark"}, {"Settings", "Bomberman", "Dark"}, {"Player", "Bomberman", "Dark"}, {"Exit", "Bomberman", "Dark"}});
    linkButtonToMenu(window, menu);
    return menu;
}

void UserInterface::create() //tmp
{
    menu = createMenuBomberman(window);
}

void UserInterface::setBackGround(const std::string &backGround)
{
    window->changeSkybox("Resources/Texture/" + backGround);
}

bool UserInterface::demo()
{
    CameraMove cameraMoove;
    World world(window, "Resources/Map/DemoWithoutEdge");
    Player player(window, "Bomberman", "Bob", &world, vector3du(1, 1, 1));
    window->applyCameraMove(cameraMoove); // tmp
    window->setDebugMode(true); // tmp

    while (window->isOpen()) {
        if (window->isKeyPressed(KEY_KEY_P))
            return true;
        world.update();
        player.update();
        window->display(); //move player
    }
    return false;
}

void UserInterface::run(const vector3df &cameraPos, const vector3df &cameraTarget)
{
    camera = window->getCameraSceneNode(cameraPos, cameraTarget);

    while (window->isOpen()) {
        if (menu->getKey() && menu->getName() == "Player")
            myPlayer = new Player(NULL, menu->getCurrentButtonModel(), "BOB", NULL, vector3du(1, 1 ,1));
        else if (menu->getKey() && menu->getName() == "Texture")
            myPlayer->changeTexture(menu->getCurrentButtonTexture());
        if (menu->getKey()) {
            if (!lock) {
                if (!menu->getMenu() && menu->getCurrentButtonName() == "Exit")
                    window->close();
                if (!menu->getMenu() && menu->getCurrentButtonName() == "Play") {
                    uint port = 8080;
                    //server(port, "Resources/Map/Default", 1); have to write in a thread
                    //client(IpAddress("127.0.0.1"), port);
                }
                if (menu->getMenu()) {
                    CameraMove cameraAnim(menu->getPosition(), menu->getMenu()->getTargetPosition(), 1);
                    cameraAnim.addPoint(menu->getMenu()->getPosition());
                    window->applyCameraMove(cameraAnim);
                    menu->setPrevMenu(menu);
                    menu = menu->getMenu();
                }
                lock = true;
            }
        }
        else
            lock = false;
        window->display();
    }
}