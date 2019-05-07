/*
** EPITECH PROJECT, 2019
** for_norme
** File description:
** Main.cpp
*/

#include <iostream> // ?
#include <irrlicht.h> // tmp
#include <cstring>

using namespace std;

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//client

//server

int main(int argc, char **argv)
{
    if (argc == 2 && strncmp(argv[1], "server", strlen(argv[1])) == 0)
        cout << "server" << endl;
    else if (argc == 1)
        cout << "client" << endl;
    else
        cerr << "USE : " << argv[0] << " [server]" << endl;
    return 0;
}
