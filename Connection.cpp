#include "Connection.h"

// Konstruktor
Connection::Connection(string host, int port, string channel) {
    this->host = host;
    this->port = port;
    this->channel = channel;
}

// Destruktor
Connection::~Connection() {
}
