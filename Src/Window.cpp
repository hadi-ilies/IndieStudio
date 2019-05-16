/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Window.cpp
*/

#include "Window.hpp"

Window::Window(const string &windowName, const dimension2d<u32> &size, const bool &fullscreen)
    : device(video::EDT_SOFTWARE, size, 16, fullscreen, false, false, TODO)
{
    if (!device)
        throw Error("device cant bo create");
    device->setWindowCaption(windowName);
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();
}

Window::~Window()
{
    device->drop();
}

bool Window::isOpen()
{
    return device->run();
}

IAnimatedMeshSceneNode *Window::addAnimatedMesh(const string &model, const string &texture)
{
    scene::ISceneManager* smgr = device->getSceneManager();
    IAnimatedMesh *mesh = smgr->getMesh(model);
    IAnimatedMeshSceneNode *node;

    if (!mesh)
        return NULL;
    node = smgr->addAnimatedMeshSceneNode(mesh);
    if (node) {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture(0, driver->getTexture(texture));
    }
    return node;
}
