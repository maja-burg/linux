#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <time.h>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

class Connection {
public:
    Connection();
    ~Connection();

    Connect();
    Disconnect();

    Identify();
    PingPong(string buffer);

private:
    string  host;
    int     port;
    string  channel;


};


#endif
