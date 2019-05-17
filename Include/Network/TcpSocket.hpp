/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** TcpSocket.hpp
*/

#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

#include <string>

using namespace std;

class TcpSocket
{
public:
    TcpSocket();
    ~TcpSocket();
    const uint &getLocalPort() const;
    const std::string &getRemoteAddress() const;
    const uint &getRemotePort() const;
    bool connect(const std::string &address, const uint &port);
    void disconnect();
    //send // TODO
    //receive // TODO

private:
    std::string remoteAddress;
    uint remotePort;
};

#endif
