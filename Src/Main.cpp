/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Main.cpp
*/

#include <iostream>
#include <cstring>
#include "World.hpp"

using namespace std;

bool tmp2()
{
    World world("// TODO");

    world.debugAff();

    IrrlichtDevice *device = createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480));

    if (!device)
        return false;
    device->setWindowCaption(L"Bomberman");

    IVideoDriver *driver = device->getVideoDriver();
    ISceneManager *smgr = device->getSceneManager();
    /*scene::ISceneNode *cube = smgr->addCubeSceneNode();

    if (cube)
    cube->setMaterialTexture(0, driver->getTexture("Resources/Texture/Wall.png"));*/

    smgr->addCameraSceneNodeFPS();
    device->getCursorControl()->setVisible(false);

    world.aff(driver, smgr);
    while(device->run()) {
        driver->beginScene(true, true, video::SColor(255,113,113,133));

        smgr->drawAll(); // draw the 3d scene
        device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)

        driver->endScene();
    }
    device->drop();
    return true;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    if (argc == 2 && strncmp(argv[1], "server", strlen(argv[1])) == 0)
        cout << "server" << endl;
    else if (argc == 1)
        cout << "client" << endl;
    else
        cerr << "USE : " << argv[0] << " [server]" << endl;
    tmp2(); // tmp
    return 0;
}
