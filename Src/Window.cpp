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
    device = createDevice(video::EDT_OPENGL, size, 16, fullscreen, false, false, &receiver);
    if (!device)
        throw Error("device cant bo create");
    //device->setWindowCaption(windowName.c_str()); // TODO
    device->setWindowCaption(L"TODO : use windowName of Window ctor"); // tmp
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    smgr->addCameraSceneNodeFPS(); // tmp
    device->getCursorControl()->setVisible(false); // tmp
}

Window::~Window()
{
    device->drop();
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

ISceneNode *Window::addCube(const f32 &size, const std::string &texture)
{
    scene::ISceneNode *node = smgr->addCubeSceneNode();

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
