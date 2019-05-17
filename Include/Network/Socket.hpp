/*
** EPITECH PROJECT, 2019
** Socket
** File description:
** Socket
*/

#ifndef SOCKET_HPP
#define SOCKET_HPP
#include <sys/socket.h>
#include <netinet/in.h>

class Socket {
public:
	enum socketType { TCP, UDP };
public:
	Socket(socketType type);
	~Socket();
protected:
private:
};
#endif /* !Socket */
