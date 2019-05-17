/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** TcpListener.hpp
*/

#ifndef TCPLISTENER_HPP
#define TCPLISTENER_HPP

#include <string>
//#include "Socket.hpp" // ?

using namespace std;

class TcpListener// : public Sokect // ?
{
public:
    TcpListener();
    ~TcpListener();
    const uint &getLocalPort() const;
    bool listen(const uint &port);
    //void close(); // ?
    bool accept(TcpSocket &socket);

private:
    std::string remoteAddress;
    uint remotePort;
};

#endif
