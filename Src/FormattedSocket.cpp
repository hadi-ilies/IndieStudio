/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** FormattedSocket.cpp
*/

#include "FormattedSocket.hpp"

/*
 * Constructors // Destructors
 */
FormattedSocket::FormattedSocket() : connected(false) {

}

FormattedSocket::~FormattedSocket() = default;

/*
 * Getters // Setters
 */
ushort FormattedSocket::getLocalPort() const {
    return socket.getLocalPort();
}

sf::IpAddress FormattedSocket::getRemoteAddress() const {
    return socket.getRemoteAddress();
}

ushort FormattedSocket::getRemotePort() const {
    return socket.getRemotePort();
}

/*
 * Methods
 */
bool FormattedSocket::connect(const sf::IpAddress &remoteAddress, const ushort &remotePort, const sf::Time &timeout) {
    connected = socket.connect(remoteAddress, remotePort, timeout) == sf::Socket::Done;
    return connected;
}

bool FormattedSocket::accept(sf::TcpListener &listener) {
    connected = listener.accept(socket) == sf::Socket::Done;
    return connected;
}

void FormattedSocket::disconnect() {
    socket.disconnect();
    connected = false;
}

bool FormattedSocket::isConnected() const {
    return connected;
}

bool FormattedSocket::sendStartTurn() {
    sf::Packet packet;

    packet << StartTurn;
    return sendPacket(packet);
}

bool FormattedSocket::sendEndTurn() {
    sf::Packet packet;

    packet << EndTurn;
    return sendPacket(packet);
}

bool FormattedSocket::sendMessage(const std::string &msg) {
    sf::Packet packet;

    packet << Message;
    packet << msg;
    return sendPacket(packet);
}

bool FormattedSocket::sendNumber(const sf::Uint32 &num) {
    sf::Packet packet;

    packet << Number;
    packet << num;
    return sendPacket(packet);
}

bool FormattedSocket::sendPosition(const vector3du &pos) {
    sf::Packet packet;

    packet << Position;
    packet << pos.X;
    packet << pos.Y;
    packet << pos.Z;
    return sendPacket(packet);
}

bool FormattedSocket::sendPlayerMove(const vector2di &dir) {
    sf::Packet packet;

    packet << PlayerMove;
    packet << dir.X;
    packet << dir.Y;
    return sendPacket(packet);
}

bool FormattedSocket::sendPlayerPutBomb() {
    sf::Packet packet;

    packet << PlayerPutBomb;
    return sendPacket(packet);
}

bool FormattedSocket::sendPlayerDisconnect() {
    sf::Packet packet;

    packet << PlayerDisconnect;
    return sendPacket(packet);
}

bool FormattedSocket::receive() {
    sf::Packet packet;

    if (!receivePacket(packet))
        return false;
    if (!(packet >> type))
        return false;
    if (type == Message) {
        if (!(packet >> message))
            return false;
    } else if (type == Number) {
        if (!(packet >> number))
            return false;
    } else if (type == Position) {
        uint x;
        uint y;
        uint z;

        if (!(packet >> x >> y >> z))
            return false;
        position.X = x;
        position.Y = y;
        position.Z = z;
    } else if (type == PlayerMove) {
        int x;
        int y;

        if (!(packet >> x >> y))
            return false;
        direction.X = x;
        direction.Y = y;
    }
    //else if (type == ...) // TODO
    return true;
}

bool FormattedSocket::sendPacket(sf::Packet &packet) {
    const sf::Socket::Status status = socket.send(packet);

    if (status == sf::Socket::Disconnected || status == sf::Socket::Error)
        connected = false;
    return status == sf::Socket::Done;
}

bool FormattedSocket::receivePacket(sf::Packet &packet) {
    const sf::Socket::Status status = socket.receive(packet);

    if (status == sf::Socket::Disconnected || status == sf::Socket::Error)
        connected = false;
    return status == sf::Socket::Done;
}

/*
 * Redefinition
 */
sf::Packet &operator>>(sf::Packet &packet, DataType &dataType) {
    sf::Uint32 tmp;

    packet >> tmp;
    dataType = (DataType) tmp;
    return packet;
}
