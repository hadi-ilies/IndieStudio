/*
** EPITECH PROJECT, 2019
** socket
** File description:
** socket
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Network/Socket.hpp"
#include "Error.hpp"

Socket::Socket(socketType type = TCP)
{

}

Socket::~Socket()
{
}

void Socket::createUdp()
{
/*    int address_family = AF_INET;
    int type = SOCK_DGRAM;
    int protocol = IPPROTO_UDP;

    if (sockfd = socket(address_family, type, protocol) == -1)
        throw Error("error has been detected in setsockopt !\n");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(0);
    addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1)
        throw Error("error has been detected in udp bind function !\n");
*/
}

void Socket::createTcp()
{
   /* struct protoent *pe = getprotobyname("TCP");
    int useless = 1;

    if (sockfd = socket(AF_INET, SOCK_STREAM, pe->p_proto) == -1)
        throw Error("error has been detected in TCP socket function !\n");
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, (const char *) &useless, sizeof(useless)) == -1)
        throw Error("error has been detected in setsockopt !\n");
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(0);
    if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1)
        throw Error("error has been detected in bind function !\n");
        */
}


/*Socket::socketType Socket::getSocketType() const {
    return type;
}
*/