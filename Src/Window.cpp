/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** Window.cpp
*/

#include "Window.hpp"
#include "Error.hpp"

Window::Window(const std::string &windowName, dimension2d<u32> size, const bool &fullscreen)
{
    const wstring title(windowName.begin(), windowName.end());

    device = createDevice(video::EDT_OPENGL, size, 16, fullscreen, false, false, &receiver);
    if (!device)
        throw Error("device cant bo create");
    device->setWindowCaption(title.c_str());
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    smgr->addCameraSceneNodeFPS(0, 100, 0.05); // tmp
    device->getCursorControl()->setVisible(false); // tmp
}

Window::~Window()
{
    close();
    device->drop();
}

void Window::close()
{
    device->closeDevice();
}

bool Window::isOpen()
{
    return device->run();
}

void Window::display(const SColor &color)
{
    driver->beginScene(true, true, color);
    smgr->drawAll();
    //device->getGUIEnvironment()->drawAll();
    driver->endScene();
}

IAnimatedMesh *Window::getModel(const std::string &fileName)
{
    return smgr->getMesh(fileName.c_str());
}

ISceneNode *Window::addCube(const std::string &texture)
{
    scene::ISceneNode *node = smgr->addCubeSceneNode(1);

    if (!node)
        return NULL;
    node->setMaterialTexture(0, driver->getTexture(texture.c_str()));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    return node;
}

IAnimatedMeshSceneNode *Window::addAnimatedMesh(const std::string &model, const std::string &texture)
{
    IAnimatedMesh *mesh = smgr->getMesh(model.c_str());
    IAnimatedMeshSceneNode *node;

    if (!mesh)
        return NULL;
    node = smgr->addAnimatedMeshSceneNode(mesh);
    if (node) {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture(0, driver->getTexture(texture.c_str()));
    }
    return node;
}

ISceneNodeAnimator *Window::createTranslation(const vector3df &initPos, const vector3df &destPos, const u32 &timestamp)
{
    return smgr->createFlyStraightAnimator(initPos, destPos, timestamp);
}


bool Window::isKeyPressed(const irr::EKEY_CODE &keyCode) const
{
    return receiver.IsKeyDown(keyCode);
}
