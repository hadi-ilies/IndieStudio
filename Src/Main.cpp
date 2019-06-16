/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Main.cpp
*/

#include <iostream>
#include <irrlicht/irrlicht.h>
#include <JukeBox.hpp>
#include "Window.hpp"
#include "World.hpp"
#include "Entity/Player.hpp"
#include "UserInterface/UserInterface.hpp"

int main(int argc, char **argv)
{
    Window window("Bomberman", dimension2d<u32>(1920, 1080), false);

    World world (&window, vector3du(7,2,7));

    world.save("Resources/Map/Game/7x7");

    /*try {
        srand(time(nullptr));
        UserInterface userInterface;

        if (userInterface.demo()) {
            userInterface.create();
            userInterface.setBackGround("BackgroundDemo.jpg");
            userInterface.run(vector3df(20, -3, 0), vector3df(10, -5, 0));
        }
    }
    catch (const Error &e) {
        std::cerr << "[" << e.where() << "]" << std::endl;
        std::cerr << "\t" << e.what() << std::endl;
    }
    catch (const exception &e) {
        std::cerr << "EXCEPTION : " << e.what() << std::endl;
    }
    return 0;*/
}

